# OpenVDL Composition Model

## Purpose

OpenVDL should treat extensibility and composability as foundational properties of the language.

The goal is not only to describe isolated validators, but to make it possible to build a reusable validator ecosystem where:

- base validators are published once
- organization and provider policies extend them
- entry-point documents aggregate validators
- conditional logic selects the right validator flow

## Core Idea

An OpenVDL file should be able to act as:

- a standalone validator
- an extension of another validator
- a reusable module referenced by other validators
- an entry-point aggregator for a set of validators

This is the right mental model:

OpenVDL is not just a rule file.

OpenVDL is a codebase of validators expressed declaratively.

## Extension

Extending a validator should be a first-class operation.

The common use case is:

- start from a standard validator
- add extra constraints
- avoid duplicating the original logic

Example:

```yaml
openvdl: "0.1"
id: "acme/email"
extends:
  - "openvdl/email/base@1"
stages:
  - id: acme-policy
    rules:
      - id: acme-domain-only
        type: domainEquals
        value: acme.com
```

This allows an organization to reuse the standard email validator while applying local policy.

## Imports and References

OpenVDL should separate inheritance from reuse.

- `extends` means "start from this validator and add more constraints"
- `imports` means "declare these validators as dependencies"
- `ref` means "use one imported validator here"

This distinction avoids semantic confusion and keeps evaluation behavior clearer.

## Aggregator Entry Points

A root OpenVDL document should be able to orchestrate multiple validators.

This is useful when the accepted value can match different families of validators, or when selection depends on context.

Example:

```yaml
openvdl: "0.1"
id: "acme/user-identifier"
imports:
  - "openvdl/email/base@1"
  - "openvdl/phone/e164@1"
  - "openvdl/employee-id/internal@2"

compose:
  anyOf:
    - ref: "openvdl/email/base@1"
    - ref: "openvdl/phone/e164@1"
    - ref: "openvdl/employee-id/internal@2"
```

Here the root file behaves like an entry point and aggregator, not merely a flat validator.

## Conditional Validation

OpenVDL should support conditional logic at composition level, not only inside primitive rules.

Examples:

- if domain is `gmail.com`, apply Gmail policy
- if country is `DE`, apply the German VAT validator
- if document type is `individual`, use fiscal code rules
- if document type is `company`, use VAT rules

For binary branching, `if` / `then` / `else` is sufficient.

For multi-branch selection, OpenVDL should support a dedicated `match`
/ `cases` construct. This is preferable to overloading nested
`if` / `else` chains because it is clearer, easier to validate, and
better suited to a validator orchestration language.

Illustrative structure:

```yaml
openvdl: "0.1"
id: "checkout-contact"
imports:
  - "openvdl/email/base@1"
  - "openvdl/phone/e164@1"

stages:
  - id: contact-selection
    if:
      field: country
      equals: IT
    then:
      ref: "openvdl/phone/e164@1"
    else:
      ref: "openvdl/email/base@1"
```

Illustrative multi-branch structure:

```yaml
openvdl: "0.1"
id: "vat-by-country"
imports:
  - "openvdl/vat/it@1"
  - "openvdl/vat/de@1"
  - "openvdl/vat/fr@1"

compose:
  match:
    field: country
    cases:
      - equals: IT
        ref: "openvdl/vat/it@1"
      - equals: DE
        ref: "openvdl/vat/de@1"
      - equals: FR
        ref: "openvdl/vat/fr@1"
    default:
      error:
        code: unsupported-country
```

## Minimal Primitive Set

The smallest useful composition model should include:

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

This is enough to support:

- reuse
- extension
- aggregation
- policy layering
- conditional orchestration

## Architectural Recommendation

OpenVDL should explicitly standardize:

1. a reusable validator module model
2. an entry-point aggregator model
3. a clear distinction between extension, reference, and composition
4. conditional orchestration across validators

That choice makes OpenVDL meaningfully stronger than a validator catalog or a schema syntax. It becomes a portable system for describing and distributing validation logic as a structured ecosystem.
