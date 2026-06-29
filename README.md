# OpenVDL

OpenVDL (Open Validation Description Language) is an open specification for describing data validation rules in a portable, machine-readable, and implementation-independent format.

The goal is to standardize the representation of validators, not a single validator implementation. A compliant engine can interpret the same OpenVDL document in any language, framework, or runtime.

## Why

Validation logic is usually embedded in source code and reimplemented repeatedly across ecosystems:

- email
- IBAN
- ISBN
- UUID
- VAT numbers
- fiscal identifiers
- phone numbers
- postal codes
- business identifiers
- banking identifiers

This creates duplicated work, inconsistent behavior, and difficult long-term maintenance.

OpenVDL proposes a different model:

- validators are data
- validation engines interpret validator descriptions
- the same validator can run across multiple implementations
- validators can be extended and composed instead of copied
- an OpenVDL file can act as an entry point that aggregates other validators

In that sense, OpenVDL is closer to what OpenAPI did for APIs than to a traditional validation library.

## Repository Structure

- [docs/internet-draft.md](docs/internet-draft.md): RFC-style Internet-Draft for the format
- [docs/specification.md](docs/specification.md): practical specification overview
- [docs/composition-model.md](docs/composition-model.md): foundational model for extension, composition, and validator aggregation
- [docs/provider-integration-model.md](docs/provider-integration-model.md): model for provider request/response contracts, truth sources, and API adaptation
- [ROADMAP.md](ROADMAP.md): working roadmap for the evolution of the spec
- [examples/email.yaml](examples/email.yaml): example email validator
- [examples/iban.yaml](examples/iban.yaml): example IBAN validator
- [examples/email-acme.yaml](examples/email-acme.yaml): example of extending a base validator
- [examples/user-identifier.yaml](examples/user-identifier.yaml): example of validator aggregation with `anyOf`
- [examples/vat-by-country.yaml](examples/vat-by-country.yaml): example of validator dispatch with `match/cases`

## Design Principles

- Declarative
- Portable
- Language independent
- Extensible
- Composable
- Deterministic
- Versionable
- Human readable

## Scope

OpenVDL describes validation logic for structured values, including:

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

It is also suitable for organization-specific or provider-specific validation policies.

## Foundational Model

OpenVDL should be treated as a reusable validator ecosystem, not just a file format for isolated rules.

The core ideas are:

- a validator can extend another validator instead of duplicating it
- a validator can import and reference other validators as reusable modules
- a validator can be composed with `allOf`, `anyOf`, `oneOf`, `not`, and conditional logic such as `if/then/else` or `match/cases`
- a root OpenVDL document can act as an entry point that aggregates other validators
- provider and organization policy should layer on top of base validators
- validation may involve both local rules and provider-backed truth-source checks
- OpenVDL should be able to describe the request/response contract of external validation providers

Typical examples:

- extend a standard email validator with company-only domain constraints
- apply Gmail-specific policy only when the domain is `gmail.com`
- aggregate email, phone, and internal employee ID validators into a single user identifier validator
- adapt a third-party validation API into a standard OpenVDL validation flow

## Validation Model

A validator is composed of one or more stages. Each stage adds constraints and produces deterministic results.

Typical flow:

1. syntax validation
2. policy validation
3. organization-specific constraints
4. final result

Every compliant implementation should return one of:

- `VALID`
- `INVALID`
- `ERROR`

## Composition Primitives

OpenVDL should support a small set of first-class primitives for reuse and orchestration:

- `extends`: inherit a base validator and add constraints
- `imports`: declare reusable validator dependencies
- `ref`: reference an imported validator
- `allOf`, `anyOf`, `oneOf`, `not`: compose validators and rules
- `if` / `then` / `else`: enable conditional validation flows
- `match` / `cases`: support structured multi-branch validator selection

This allows an OpenVDL file to behave like the root of a validator codebase rather than a single flat rule list.

## Provider Integration

OpenVDL should not stop at local validation rules.

Some validations depend on external truth sources, such as:

- government registries
- tax databases
- banking systems
- business registries
- domain infrastructure
- trusted validation providers

For those cases, OpenVDL should describe:

- the request shape sent to a validation provider
- the response shape returned by that provider
- how provider responses map back into OpenVDL result semantics
- how third-party APIs can be adapted into a standard OpenVDL validation model

One open architectural question is whether providers should implement OpenVDL natively, or whether OpenVDL should define an adapter layer that formalizes how arbitrary provider APIs are integrated.

## Status

This repository currently contains a draft specification intended for discussion and experimentation. It is not yet a final standard.

Current work is tracked in [ROADMAP.md](ROADMAP.md).
