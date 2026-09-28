# Open Validation Description Language (OpenVDL)

## Abstract

This document defines the Open Validation Description Language (OpenVDL), a declarative language for describing validation rules independently of implementation languages. OpenVDL enables interoperable validation of structured values by expressing constraints, algorithms, conditional rules, and composition using a standardized portable specification.

## Status of This Memo

This document is a draft specification of the OpenVDL project, written in the style of an IETF Internet-Draft. It has not been submitted to the IETF and has no IETF standing. The authors intend to submit it as an individual Internet-Draft.

It is intended for discussion and experimentation. No implementation is required to conform at this stage.

## 1. Introduction

Validation logic is traditionally embedded within application source code. This duplicates effort across ecosystems and often produces inconsistent implementations.

OpenVDL introduces a portable representation of validation semantics. Instead of implementing validators repeatedly, applications implement a single OpenVDL parser and interpreter capable of evaluating shared validator descriptions.

The primary purpose of OpenVDL is to standardize the representation of validators.

OpenVDL is further intended to support a reusable validation ecosystem in which validators can be extended, referenced, aggregated, and composed without rewriting existing logic.

OpenVDL may also need to represent factual world knowledge that materially affects validation outcomes.

## 2. Terminology

### Validator

A complete validation specification.

### Rule

A single validation constraint.

### Constraint

A property that must hold for a value to be considered valid.

### Validation Engine

Software capable of parsing and evaluating OpenVDL documents.

### Registry

A repository of published validators.

### Aggregator

A root OpenVDL document that imports, references, and orchestrates other validators.

## 3. Requirements Language

The key words "MUST", "SHOULD", "MAY", "MUST NOT", and "SHOULD NOT" in this document are to be interpreted as described in RFC 2119.

## 4. Goals

OpenVDL is designed to be:

- declarative
- portable
- language independent
- extensible
- composable
- deterministic
- versionable
- human readable

## 5. Scope

OpenVDL describes validation logic for structured values, including but not limited to:

- email addresses
- URLs
- UUIDs
- IP addresses
- IBAN
- BIC
- ISBN
- credit cards
- national identifiers
- VAT numbers
- postal codes
- vehicle identification numbers
- domain names
- phone numbers
- product codes

The format is also suitable for organization-specific validation policies.

It may also be suitable for validation workflows that depend on external providers and authoritative truth sources.

## 6. Validation Model

A validator is composed of one or more validation stages. Each stage contributes additional constraints.

Illustrative pipeline:

1. syntax validation
2. provider policy
3. organization policy
4. final decision

Each implementation MUST evaluate stages deterministically.

## 7. Architecture

High-level processing model:

1. load validator document
2. parse document structure
3. resolve references
4. evaluate stages and rules
5. return validation result and diagnostics

An OpenVDL document MAY act either as a standalone validator or as an aggregator that coordinates other validators.

## 8. Rule Categories

### 8.1 Structural Rules

Structural rules include:

- length
- character sets
- encoding
- Unicode support
- normalization
- whitespace behavior
- allowed symbols
- forbidden symbols

### 8.2 Pattern Rules

Pattern rules include:

- regular expressions
- prefixes
- suffixes
- character classes
- token ordering

### 8.3 Numeric Rules

Numeric rules include:

- ranges
- modulo
- checksums
- digit verification
- parity

### 8.4 Algorithmic Rules

Algorithmic rules include:

- Luhn
- Mod97
- ISO algorithms
- national algorithms
- custom named algorithms

### 8.5 Conditional Rules

Conditional rules include:

- `if`
- `else`
- `switch`
- `match`
- `cases`
- country-dependent policies
- provider-dependent policies
- version-dependent policies

### 8.6 Composite Rules

Composite rules include:

- `and`
- `or`
- `not`
- nested validators
- referenced validators

### 8.7 External Rules

External rules may include:

- DNS lookups
- HTTP lookups
- certificate verification
- public key verification
- directory lookups
- remote policy retrieval

Support for external rules SHOULD be capability-gated and MAY be disabled in constrained implementations.

## 9. Composition

Validators MAY extend, import, reference, and compose other validators.

OpenVDL SHOULD support distinct primitives for:

- `extends`
- `imports`
- `ref`
- `allOf`
- `anyOf`
- `oneOf`
- `not`
- `if`
- `then`
- `else`
- `match`
- `cases`

For example, an email validator may:

1. extend an RFC-based syntax validator
2. add a provider policy such as `gmail.com`
3. add organization-specific policy

This model allows reusable building blocks and layered policies without duplicated code.

An OpenVDL root document MAY also act as an aggregator. In that role it imports reusable validators and defines orchestration logic over them, for example:

1. accept email OR phone OR internal employee identifier
2. select a country-specific validator based on input context
3. apply provider policy only when provider conditions match

## 10. Provider Policies

Providers MAY publish additional validation constraints that extend a base validator.

Example provider-specific behavior could include:

- forbidding underscore characters
- ignoring dots for account identity
- supporting plus-addressing

Applications SHOULD consume provider policy definitions through the same OpenVDL format instead of embedding provider-specific logic in application code.

## 11. Provider-Backed Validation

Some validation workflows depend on external providers or authoritative truth sources rather than solely on local rule evaluation.

Examples include:

- government registries
- tax authority systems
- business registries
- banking systems
- third-party validation APIs

OpenVDL SHOULD be able to describe:

- the request structure sent to a validation provider
- the response structure returned by a validation provider
- the mapping from provider response fields to OpenVDL result semantics
- capability and trust requirements for provider-backed validation

Two architectural models are possible:

1. providers conform directly to OpenVDL request and response contracts
2. OpenVDL defines an adapter model for integrating third-party APIs that do not natively implement OpenVDL

The adapter model may be more deployable in practice because many validation providers already expose established APIs that cannot easily be replaced.

## 12. Facts and World Knowledge

Some validators depend on factual world knowledge that changes over time, such as numbering plans, provider behavior, registry policy, or allocation status.

Such facts SHOULD be representable within OpenVDL documents as part of validator semantics rather than being left solely to external human-readable notes.

An implementation-facing fact representation SHOULD be able to carry:

- subject
- factual statement
- impact on validation behavior
- provenance or source reference
- confidence level
- effective date or revision interval

External notes MAY exist for explanation or editorial detail, but they SHOULD NOT be the sole semantic carrier of facts that materially affect validation outcomes.

## 13. Result Model

Every compliant implementation MUST return exactly one of the following outcomes:

- `VALID`
- `INVALID`
- `ERROR`

`VALID` means all applicable constraints succeeded.

`INVALID` means at least one validation rule failed.

`ERROR` means evaluation could not complete deterministically, for example due to malformed validator definitions, unresolved references, or unavailable required capabilities.

## 14. Error Reporting

Validation engines SHOULD expose structured diagnostics.

A diagnostic SHOULD include:

- rule identifier
- location
- expected condition
- actual observed value or state
- machine-readable error code

Illustrative diagnostic:

```text
ruleId: email.local.maxLength
location: local-part
expected: maximum length 64
actual: length 71
```

## 15. Versioning

Validators are immutable.

Breaking changes MUST require a new version. Implementations and applications SHOULD be able to select validator versions explicitly.

## 16. Distribution

Validators SHOULD be distributable independently from software implementations.

Possible mechanisms include:

- Git repositories
- package managers
- DNS records
- well-known URLs
- registry services
- enterprise repositories

Illustrative identifiers:

- `/openvdl/email`
- `/openvdl/iban`
- `/openvdl/isbn`

## 17. Conformance

An implementation conforms to this draft if it:

- correctly parses supported OpenVDL documents
- evaluates all mandatory rule types it claims to support
- produces deterministic results
- reports structured validation diagnostics

Capability declarations SHOULD clearly identify unsupported optional features, especially external lookup features.

## 18. Security Considerations

Validators MUST NOT execute arbitrary code.

Recursive references MUST be detected and bounded.

External lookups SHOULD be sandboxed.

Implementations SHOULD enforce denial-of-service protections, including limits for recursion depth, input size, evaluation steps, and network behavior.

## 19. IANA Considerations

Future versions may request registration of media types such as:

- `application/openvdl+yaml`
- `application/openvdl+json`
- `application/openvdl+xml`

This document makes no current IANA requests.

## 20. References

- RFC 2119
- RFC 5234
- RFC 5321
- RFC 5322
- RFC 6531
- ISO 13616
- ISO 7064

## 21. Acknowledgments

Acknowledgment is due to contributors interested in making validation portable, deterministic, and implementation-independent.
