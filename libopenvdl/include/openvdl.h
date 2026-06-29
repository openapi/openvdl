#ifndef OPENVDL_H
#define OPENVDL_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OPENVDL_MAX_STAGES 16
#define OPENVDL_MAX_RULES_PER_STAGE 32

typedef enum {
    OPENVDL_VALID = 0,
    OPENVDL_INVALID = 1,
    OPENVDL_ERROR = 2
} openvdl_result_code;

typedef enum {
    OPENVDL_RULE_MIN_LENGTH = 0,
    OPENVDL_RULE_MAX_LENGTH = 1,
    OPENVDL_RULE_CONTAINS_CHAR = 2,
    OPENVDL_RULE_DOMAIN_EQUALS = 3,
    OPENVDL_RULE_PART_MIN_LENGTH = 4,
    OPENVDL_RULE_PART_MAX_LENGTH = 5
} openvdl_rule_type;

typedef enum {
    OPENVDL_PART_FULL = 0,
    OPENVDL_PART_LOCAL = 1,
    OPENVDL_PART_DOMAIN = 2
} openvdl_part;

typedef struct {
    const char *rule_id;
    const char *stage_id;
    const char *location;
    const char *message;
    size_t expected;
    size_t actual;
} openvdl_diagnostic;

typedef struct {
    openvdl_rule_type type;
    const char *id;
    openvdl_part part;
    size_t threshold;
    char ch;
    const char *text;
} openvdl_rule;

typedef struct {
    const char *id;
    size_t rule_count;
    const openvdl_rule *rules;
} openvdl_stage;

typedef struct {
    const char *id;
    size_t stage_count;
    const openvdl_stage *stages;
} openvdl_validator;

typedef struct {
    openvdl_result_code code;
    openvdl_diagnostic diagnostic;
} openvdl_result;

openvdl_result openvdl_validate_string(const openvdl_validator *validator,
                                       const char *value);

const char *openvdl_result_code_name(openvdl_result_code code);

openvdl_rule openvdl_rule_min_length(const char *id, size_t min_length);
openvdl_rule openvdl_rule_max_length(const char *id, size_t max_length);
openvdl_rule openvdl_rule_contains_char(const char *id, char ch);
openvdl_rule openvdl_rule_domain_equals(const char *id, const char *domain);
openvdl_rule openvdl_rule_part_min_length(const char *id,
                                          openvdl_part part,
                                          size_t min_length);
openvdl_rule openvdl_rule_part_max_length(const char *id,
                                          openvdl_part part,
                                          size_t max_length);

#ifdef __cplusplus
}
#endif

#endif
