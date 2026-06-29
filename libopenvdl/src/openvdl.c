#include "openvdl.h"

#include <string.h>

typedef struct {
    const char *ptr;
    size_t len;
} openvdl_slice;

static openvdl_slice openvdl_full_slice(const char *value) {
    openvdl_slice slice;

    slice.ptr = value;
    slice.len = value == NULL ? 0 : strlen(value);
    return slice;
}

static int openvdl_email_parts(const char *value,
                               openvdl_slice *local_part,
                               openvdl_slice *domain_part) {
    const char *at;

    if (value == NULL || local_part == NULL || domain_part == NULL) {
        return 0;
    }

    at = strchr(value, '@');
    if (at == NULL) {
        return 0;
    }

    local_part->ptr = value;
    local_part->len = (size_t)(at - value);
    domain_part->ptr = at + 1;
    domain_part->len = strlen(at + 1);
    return 1;
}

static openvdl_slice openvdl_slice_for_part(const char *value,
                                            openvdl_part part,
                                            int *ok) {
    openvdl_slice full;
    openvdl_slice local_part;
    openvdl_slice domain_part;

    full = openvdl_full_slice(value);
    *ok = 1;

    switch (part) {
        case OPENVDL_PART_FULL:
            return full;
        case OPENVDL_PART_LOCAL:
            if (!openvdl_email_parts(value, &local_part, &domain_part)) {
                *ok = 0;
                return full;
            }
            return local_part;
        case OPENVDL_PART_DOMAIN:
            if (!openvdl_email_parts(value, &local_part, &domain_part)) {
                *ok = 0;
                return full;
            }
            return domain_part;
        default:
            *ok = 0;
            return full;
    }
}

static openvdl_result openvdl_error_result(const char *message) {
    openvdl_result result;

    result.code = OPENVDL_ERROR;
    result.diagnostic.rule_id = NULL;
    result.diagnostic.stage_id = NULL;
    result.diagnostic.location = NULL;
    result.diagnostic.message = message;
    result.diagnostic.expected = 0;
    result.diagnostic.actual = 0;
    return result;
}

static openvdl_result openvdl_invalid_result(const openvdl_stage *stage,
                                             const openvdl_rule *rule,
                                             const char *location,
                                             const char *message,
                                             size_t expected,
                                             size_t actual) {
    openvdl_result result;

    result.code = OPENVDL_INVALID;
    result.diagnostic.rule_id = rule->id;
    result.diagnostic.stage_id = stage->id;
    result.diagnostic.location = location;
    result.diagnostic.message = message;
    result.diagnostic.expected = expected;
    result.diagnostic.actual = actual;
    return result;
}

static int openvdl_contains_char(const char *value, char ch) {
    if (value == NULL) {
        return 0;
    }

    return strchr(value, ch) != NULL;
}

static int openvdl_slice_equals_cstr(openvdl_slice slice, const char *text) {
    size_t len;

    if (text == NULL) {
        return 0;
    }

    len = strlen(text);
    if (slice.len != len) {
        return 0;
    }

    return strncmp(slice.ptr, text, slice.len) == 0;
}

static openvdl_result openvdl_apply_rule(const openvdl_stage *stage,
                                         const openvdl_rule *rule,
                                         const char *value) {
    int ok;
    openvdl_slice slice;
    openvdl_slice local_part;
    openvdl_slice domain_part;

    switch (rule->type) {
        case OPENVDL_RULE_MIN_LENGTH:
            if (openvdl_full_slice(value).len < rule->threshold) {
                return openvdl_invalid_result(stage, rule, "value",
                                              "minimum length not met",
                                              rule->threshold,
                                              openvdl_full_slice(value).len);
            }
            break;
        case OPENVDL_RULE_MAX_LENGTH:
            if (openvdl_full_slice(value).len > rule->threshold) {
                return openvdl_invalid_result(stage, rule, "value",
                                              "maximum length exceeded",
                                              rule->threshold,
                                              openvdl_full_slice(value).len);
            }
            break;
        case OPENVDL_RULE_CONTAINS_CHAR:
            if (!openvdl_contains_char(value, rule->ch)) {
                return openvdl_invalid_result(stage, rule, "value",
                                              "required character missing",
                                              (size_t)(unsigned char)rule->ch,
                                              0);
            }
            break;
        case OPENVDL_RULE_DOMAIN_EQUALS:
            if (!openvdl_email_parts(value, &local_part, &domain_part)) {
                return openvdl_invalid_result(stage, rule, "domain",
                                              "domain comparison requires an email-like value",
                                              1, 0);
            }
            if (!openvdl_slice_equals_cstr(domain_part, rule->text)) {
                return openvdl_invalid_result(stage, rule, "domain",
                                              "domain did not match expected value",
                                              strlen(rule->text),
                                              domain_part.len);
            }
            break;
        case OPENVDL_RULE_PART_MIN_LENGTH:
            slice = openvdl_slice_for_part(value, rule->part, &ok);
            if (!ok) {
                return openvdl_error_result("unable to resolve rule part");
            }
            if (slice.len < rule->threshold) {
                return openvdl_invalid_result(stage, rule,
                                              rule->part == OPENVDL_PART_LOCAL ? "local-part" : "domain",
                                              "minimum part length not met",
                                              rule->threshold, slice.len);
            }
            break;
        case OPENVDL_RULE_PART_MAX_LENGTH:
            slice = openvdl_slice_for_part(value, rule->part, &ok);
            if (!ok) {
                return openvdl_error_result("unable to resolve rule part");
            }
            if (slice.len > rule->threshold) {
                return openvdl_invalid_result(stage, rule,
                                              rule->part == OPENVDL_PART_LOCAL ? "local-part" : "domain",
                                              "maximum part length exceeded",
                                              rule->threshold, slice.len);
            }
            break;
        default:
            return openvdl_error_result("unknown rule type");
    }

    return (openvdl_result){OPENVDL_VALID, {0}};
}

openvdl_result openvdl_validate_string(const openvdl_validator *validator,
                                       const char *value) {
    size_t i;
    size_t j;
    openvdl_result result;

    if (validator == NULL || value == NULL) {
        return openvdl_error_result("validator and value are required");
    }

    if (validator->stage_count > OPENVDL_MAX_STAGES) {
        return openvdl_error_result("stage count exceeds scaffold limit");
    }

    for (i = 0; i < validator->stage_count; ++i) {
        const openvdl_stage *stage = &validator->stages[i];

        if (stage->rule_count > OPENVDL_MAX_RULES_PER_STAGE) {
            return openvdl_error_result("rule count exceeds scaffold limit");
        }

        for (j = 0; j < stage->rule_count; ++j) {
            result = openvdl_apply_rule(stage, &stage->rules[j], value);
            if (result.code != OPENVDL_VALID) {
                return result;
            }
        }
    }

    return (openvdl_result){OPENVDL_VALID, {0}};
}

const char *openvdl_result_code_name(openvdl_result_code code) {
    switch (code) {
        case OPENVDL_VALID:
            return "VALID";
        case OPENVDL_INVALID:
            return "INVALID";
        case OPENVDL_ERROR:
            return "ERROR";
        default:
            return "ERROR";
    }
}

openvdl_rule openvdl_rule_min_length(const char *id, size_t min_length) {
    return (openvdl_rule){OPENVDL_RULE_MIN_LENGTH, id, OPENVDL_PART_FULL,
                          min_length, 0, NULL};
}

openvdl_rule openvdl_rule_max_length(const char *id, size_t max_length) {
    return (openvdl_rule){OPENVDL_RULE_MAX_LENGTH, id, OPENVDL_PART_FULL,
                          max_length, 0, NULL};
}

openvdl_rule openvdl_rule_contains_char(const char *id, char ch) {
    return (openvdl_rule){OPENVDL_RULE_CONTAINS_CHAR, id, OPENVDL_PART_FULL,
                          0, ch, NULL};
}

openvdl_rule openvdl_rule_domain_equals(const char *id, const char *domain) {
    return (openvdl_rule){OPENVDL_RULE_DOMAIN_EQUALS, id, OPENVDL_PART_DOMAIN,
                          0, 0, domain};
}

openvdl_rule openvdl_rule_part_min_length(const char *id,
                                          openvdl_part part,
                                          size_t min_length) {
    return (openvdl_rule){OPENVDL_RULE_PART_MIN_LENGTH, id, part,
                          min_length, 0, NULL};
}

openvdl_rule openvdl_rule_part_max_length(const char *id,
                                          openvdl_part part,
                                          size_t max_length) {
    return (openvdl_rule){OPENVDL_RULE_PART_MAX_LENGTH, id, part,
                          max_length, 0, NULL};
}
