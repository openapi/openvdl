# OpenVDL Specification Overview

## Mission

OpenVDL defines a portable format for describing validation logic as data.

Instead of reimplementing validators in each language, applications implement an OpenVDL parser and interpreter.

OpenVDL is intended to model a reusable validator codebase, where validators can be extended, referenced, aggregated, and composed declaratively.

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

### Aggregator

A root OpenVDL document that orchestrates multiple validators as an entry point.

## Design Model

Validators may be:

- standalone
- composed from reusable validators
- extended with provider-specific policies
- extended with organization-specific rules
- used as entry-point aggregators for other validators

Example progression for email validation:

1. RFC syntax
2. provider policy
3. organization policy

## Foundational Principles

OpenVDL should provide native support for:

- extension of base validators without copy-paste
- composition of multiple validators into higher-level validators
- conditional activation of rules or validators
- layered policy application
- root documents that aggregate validators from a shared validator set
- multi-branch validator selection through explicit matching
- provider-backed validation flows based on authoritative truth sources
- embedded fact semantics for world knowledge that affects validation behavior

This makes OpenVDL closer to a distributed validator codebase than to a simple schema file.

## Facts as First-Class Semantics

OpenVDL should support explicit representation of world facts that influence validator behavior.

These are not merely comments. They are part of the semantic basis for why a validator accepts, rejects, routes, or deprecates values.

Examples include:

- numbering-plan changes
- provider policy changes
- identifier allocation changes
- registry behavior changes
- deprecation of value ranges

An OpenVDL fact model should allow a validator to express, at minimum:

- subject
- factual statement
- validation impact
- provenance
- confidence
- effective date

Separate explanatory notes may still exist, but the essential fact representation should remain inside the OpenVDL document model so implementations and maintainers do not lose critical meaning.

## Reuse and Composition Primitives

The model should distinguish clearly between:

- `extends`: inherit a validator and add constraints
- `imports`: declare reusable dependencies
- `ref`: reference an imported validator
- composition operators: `allOf`, `anyOf`, `oneOf`, `not`
- conditional operators: `if`, `then`, `else`
- multi-branch conditional operators: `match`, `cases`

These concepts should remain semantically separate. Extension is not the same as reference, and reference is not the same as composition.

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
- `match`
- `cases`
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

An OpenVDL root document may also work primarily as an aggregator. In that model, the root file imports validators and orchestrates them into a final validation flow.

Illustrative examples:

- accept email OR phone OR internal employee ID
- use a national VAT validator selected by country
- extend a base email validator with organization-specific domain policy
- apply provider rules only when the provider condition matches

## Provider-Backed Validation

OpenVDL should cover not only local validation logic, but also provider-backed validation based on external truth sources.

Examples include:

- VAT validation against national registries
- business identifier checks against chamber-of-commerce style databases
- banking checks against external banking systems
- domain or certificate checks against network-based sources

This implies that OpenVDL may need to standardize:

- provider request contracts
- provider response contracts
- response-to-result mapping
- capability declarations for networked or authoritative checks
- adapter definitions for third-party APIs that do not speak OpenVDL natively

Two models are possible:

1. native provider conformance, where providers expose OpenVDL-compatible request/response semantics directly
2. adapter-based conformance, where OpenVDL defines a way to wrap external provider APIs behind a formal mapping layer

The second model is likely more realistic for adoption because most truth-source providers already expose existing APIs.

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
