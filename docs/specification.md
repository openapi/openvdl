# OpenVDL Specification Overview

## Mission

OpenVDL defines a portable format for describing validation logic as data.

Instead of reimplementing validators in each language, applications implement an OpenVDL parser and interpreter.

## Core Concepts

### Validator

A complete validation specification for a value or value family.

### Rule

A single validation constraint.

### Stage

A group of rules evaluated as part of a validation pipeline.

### Validation Engine

Software that parses and evaluates OpenVDL documents.

### Registry

A repository or distribution mechanism for published validators.

## Design Model

Validators may be:

- standalone
- composed from reusable validators
- extended with provider-specific policies
- extended with organization-specific rules

Example progression for email validation:

1. RFC syntax
2. provider policy
3. organization policy

## Rule Categories

### Structural Rules

- length
- character sets
- encoding
- Unicode support
- normalization
- whitespace
- allowed symbols
- forbidden symbols

### Pattern Rules

- regular expressions
- prefixes
- suffixes
- character classes
- token ordering

### Numeric Rules

- ranges
- modulo
- checksums
- digit verification
- parity

### Algorithmic Rules

- Luhn
- Mod97
- ISO algorithms
- national algorithms
- custom named algorithms

### Conditional Rules

- `if`
- `else`
- `switch`
- country-dependent behavior
- provider-dependent behavior
- version-dependent behavior

### Composite Rules

- `and`
- `or`
- `not`
- nested validators
- referenced validators

### External Rules

- DNS lookup
- HTTP lookup
- certificate verification
- public key verification
- directory lookup
- remote policy retrieval

External rules should remain optional so offline and sandboxed implementations remain possible.

## Composition

Validators may import or reference other validators.

Example:

- `email/base/rfc5322`
- `email/provider/gmail`
- `email/org/example-corp`

Each validator remains reusable and independently versioned.

## Deterministic Validation

Every compliant implementation must produce the same result for the same input and validator definition, subject to the same enabled capabilities.

Result values:

- `VALID`
- `INVALID`
- `ERROR`

## Error Reporting

Validation engines should emit structured diagnostics, including:

- rule identifier
- location
- expected condition
- actual value or observed state
- machine-readable error code

Example fields:

- `ruleId: email.local.maxLength`
- `location: local-part`
- `expected: maximum length 64`
- `actual: length 71`

## Versioning

Validators are immutable once published.

Breaking changes require a new version identifier. Applications should be able to select validator versions explicitly.

## Distribution

Possible publication mechanisms include:

- Git repositories
- package managers
- DNS records
- well-known URLs
- registry services
- enterprise repositories

Illustrative paths:

- `/openvdl/email`
- `/openvdl/iban`
- `/openvdl/isbn`

## Security

- validators must never execute arbitrary code
- recursion must be bounded
- external lookups should be optional and sandboxed
- implementations should enforce resource limits

## Future Extensions

- digital signatures
- validator registries
- capability negotiation
- semantic validation
- policy inheritance
- localization
- streaming validation
- incremental validation
- AI-assisted validator generation
