#include "openvdl.h"

#include <assert.h>
#include <stdio.h>

static void test_valid_email_like_validator(void) {
    const openvdl_rule syntax_rules[] = {
        openvdl_rule_max_length("email.max-length", 254),
        openvdl_rule_contains_char("email.contains-at", '@'),
        openvdl_rule_part_max_length("email.local.max-length",
                                     OPENVDL_PART_LOCAL, 64),
        openvdl_rule_part_max_length("email.domain.max-length",
                                     OPENVDL_PART_DOMAIN, 253)
    };
    const openvdl_rule policy_rules[] = {
        openvdl_rule_domain_equals("email.domain.acme", "acme.com")
    };
    const openvdl_stage stages[] = {
        {"syntax", 4, syntax_rules},
        {"policy", 1, policy_rules}
    };
    const openvdl_validator validator = {
        "acme/email", 2, stages
    };
    openvdl_result result = openvdl_validate_string(&validator,
                                                    "alice@acme.com");

    assert(result.code == OPENVDL_VALID);
}

static void test_invalid_domain(void) {
    const openvdl_rule rules[] = {
        openvdl_rule_contains_char("email.contains-at", '@'),
        openvdl_rule_domain_equals("email.domain.acme", "acme.com")
    };
    const openvdl_stage stages[] = {
        {"policy", 2, rules}
    };
    const openvdl_validator validator = {
        "acme/email", 1, stages
    };
    openvdl_result result = openvdl_validate_string(&validator,
                                                    "alice@example.com");

    assert(result.code == OPENVDL_INVALID);
    assert(result.diagnostic.rule_id != NULL);
    assert(result.diagnostic.stage_id != NULL);
}

static void test_invalid_part_length(void) {
    const openvdl_rule rules[] = {
        openvdl_rule_contains_char("email.contains-at", '@'),
        openvdl_rule_part_min_length("email.local.min-length",
                                     OPENVDL_PART_LOCAL, 3)
    };
    const openvdl_stage stages[] = {
        {"syntax", 2, rules}
    };
    const openvdl_validator validator = {
        "email/min-local", 1, stages
    };
    openvdl_result result = openvdl_validate_string(&validator, "ab@acme.com");

    assert(result.code == OPENVDL_INVALID);
    assert(result.diagnostic.expected == 3);
    assert(result.diagnostic.actual == 2);
}

static void test_error_for_missing_validator(void) {
    openvdl_result result = openvdl_validate_string(NULL, "alice@acme.com");

    assert(result.code == OPENVDL_ERROR);
}

int main(void) {
    test_valid_email_like_validator();
    test_invalid_domain();
    test_invalid_part_length();
    test_error_for_missing_validator();
    printf("libopenvdl tests passed\n");
    return 0;
}
