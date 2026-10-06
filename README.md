# OpenVDL

**Portable validation rules, defined as data.**

[![Status: v0.1 draft](https://img.shields.io/badge/status-v0.1%20draft-amber)](#status)
[![Code and validators: Apache 2.0](https://img.shields.io/badge/code%20%26%20validators-Apache%202.0-blue)](LICENSE)
[![Specification and docs: CC BY 4.0](https://img.shields.io/badge/spec%20%26%20docs-CC%20BY%204.0-blue)](LICENSE-SPEC)
[![Contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen)](CONTRIBUTING.md)

OpenVDL (Open Validation Description Language) is a draft open specification for
expressing data validation rules as portable, versioned documents. The goal is to
let applications in different languages share the same definition of what makes
a value valid.

[Read the specification](docs/specification.md) · [Explore examples](examples) ·
[View the roadmap](ROADMAP.md) · [Contribute](CONTRIBUTING.md)

> **Early-stage project:** the specification is a v0.1 draft, and the reference
> runtime is a scaffold. Examples illustrate the proposed format; support across
> independent engines still needs to be built and tested.

## Why OpenVDL?

An email address, IBAN, or VAT number often gets checked in several services,
each with its own copy of the rules. Those copies drift as formats and policies
change, making it difficult to explain why the same value passes in one place
and fails in another.

OpenVDL proposes keeping the definition in a document that teams can read,
review, and version together:

- **Define once:** describe inputs, normalization steps, and named validation rules.
- **Reuse and compose:** extend base validators and combine them into larger flows.
- **Keep the context:** record the facts and sources behind a rule as it evolves.
- **Share across languages:** give engines a common definition to interpret.

The specification covers the representation and evaluation of validators.
Consistent behavior across implementations is a design goal that requires precise
semantics and shared conformance tests.

## A first look

Suppose an internal service accepts email addresses only at `acme.com`. This
excerpt from [the email extension example](examples/email-acme.yaml) declares
the base validator and adds the domain policy:

```yaml
openvdl: "0.1"
id: "acme/email"
version: "1.0.0"
extends:
  - "openvdl/email@1"
stages:
  - id: acme-policy
    rules:
      - id: acme-domain-only
        type: domainEquals
        value: acme.com
```

The shared email rules and the local policy have separate definitions, with an
explicit dependency between them. The full example adds a local-part length
constraint and declares the input and result model.

Explore [IBAN checks](examples/iban.yaml),
[alternative identifiers with `anyOf`](examples/user-identifier.yaml), or
[VAT routing by country](examples/vat-by-country.yaml).

## Design at a glance

| Principle | What it means |
|---|---|
| Declarative and readable | Rules are documents that people can inspect and engines can interpret. |
| Portable | Definitions are independent of application languages and frameworks. |
| Composable | Shared validators can be extended, referenced, and combined. |
| Versioned | Changes to definitions and their dependencies can be tracked explicitly. |
| Deterministic | Compliant engines should agree for the same input, definition, and enabled capabilities. |

The intended scope includes email, URLs, domains, IP addresses, UUIDs, IBANs,
BICs, ISBNs, payment card numbers, national and business identifiers, VAT numbers,
phone numbers, postal codes, vehicle identifiers, and product codes. Provider
and organization policies can layer additional constraints on top.

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
- OpenVDL documents should be able to embed world facts that justify validator evolution

Typical examples:

- extend a standard email validator with company-only domain constraints
- apply Gmail-specific policy only when the domain is `gmail.com`
- aggregate email, phone, and internal employee ID validators into a single user identifier validator
- adapt a third-party validation API into a standard OpenVDL validation flow
- maintain a curated validator catalog whose changes are traceable to real-world facts encoded in the validator semantics

## Validation Model

The draft organizes a validator into stages, such as syntax checks, provider
policy, and organization constraints. Evaluation produces one of three results:

| Result | Meaning |
|---|---|
| `VALID` | All applicable constraints passed. |
| `INVALID` | A validation rule failed. |
| `ERROR` | Evaluation could not complete, for example because a required reference could not be resolved. |

Structured diagnostics can identify the rule, location, and expected condition
behind a result.

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

## Facts Semantics

OpenVDL should treat facts about the world as part of validator semantics, not as side documentation.

If a validator depends on a discovered real-world constraint, that fact should be representable inside the OpenVDL document itself, with fields such as:

- subject
- statement
- impact on validation
- provenance
- confidence
- effective date or revision window

Separate notes may still exist as supporting material, but they should not be the primary semantic source. The validator document must carry the essential fact model so implementations and maintainers do not lose critical context.

## Exploration Diary

OpenVDL should also preserve the discovery process behind maintained validator changes.

Modern LLM and agentic tools make it possible to run iterative explorations over world facts that may later affect validation semantics. Those explorations should be logged as research rounds, hypotheses, and findings.

That diary is useful for:

- preserving how a fact was discovered
- retaining failed or partial hypotheses
- linking validator changes back to exploration rounds
- supporting future re-evaluation when the world changes again

The intended split is:

- OpenVDL validator documents contain the canonical semantic facts
- the exploration diary records how those facts were discovered and promoted

## Status

This repository currently contains a draft specification intended for discussion and experimentation. It is not yet a final standard.

The specification is written as an RFC-style draft ([RFC-OpenVDL.txt](RFC-OpenVDL.txt)). It has not been submitted to the IETF yet; the intention is to submit it as an individual Internet-Draft.

Contributions are welcome: see [CONTRIBUTING.md](CONTRIBUTING.md).

Current work is tracked in [ROADMAP.md](ROADMAP.md).

An early runtime scaffold is available in [libopenvdl/](libopenvdl).

A curated maintained validator library scaffold is available in [validators/](validators), with [validators/openvdl.yml](validators/openvdl.yml) as its current entry point.

An exploration diary scaffold is available in [explorations/](explorations), with [explorations/index.md](explorations/index.md) as its current index.

## Find your way around

| Start here | What you will find |
|---|---|
| [Specification overview](docs/specification.md) | Core concepts and the proposed data model. |
| [RFC-style draft](docs/internet-draft.md) | The formal draft, not yet submitted to the IETF. |
| [Composition model](docs/composition-model.md) | Extension, references, and validator aggregation. |
| [Provider integration](docs/provider-integration-model.md) | External sources and API adaptation. |
| [Examples](examples) | Email, IBAN, extension, composition, and country dispatch. |
| [Validator library](validators) | The initial catalog and its `openvdl.yml` entry point. |
| [Reference runtime](libopenvdl) | The early C implementation scaffold. |
| [Exploration diary](explorations) | Research rounds behind proposed facts and rules. |
| [Roadmap](ROADMAP.md) | Open questions and planned work. |

## Get involved

Pick a format you know well and try describing its rules. Useful contributions
include validator definitions, authoritative sources, test vectors, feedback on
ambiguous semantics, and independent engines.

Read [CONTRIBUTING.md](CONTRIBUTING.md) or
[open an issue](https://github.com/openapi/openvdl/issues) to start a discussion.

## Related Work

Declarative validation is not a new idea: LIVR, JSON Schema, CEL/Protovalidate,
libphonenumber and python-stdnum all move parts of validation out of application code.
OpenVDL focuses on the layer they leave open: a shared, versioned definition of what
"valid" means for real-world identifiers, where that knowledge comes from, and when it
changed. See [docs/related-work.md](docs/related-work.md) for the survey and the
alignment direction (CEL, JSON Schema bridge, generation from authoritative data,
conformance suite).

## License

OpenVDL uses two licenses:

- **Code and validator documents**, under [Apache License 2.0](LICENSE):
  - [libopenvdl/](libopenvdl)
  - [examples/](examples)
  - [validators/](validators)
- **Specification and documentation**, under [Creative Commons Attribution 4.0 International (CC BY 4.0)](LICENSE-SPEC):
  - [RFC-OpenVDL.txt](RFC-OpenVDL.txt)
  - [docs/](docs)
  - [explorations/](explorations)
  - this README and the other Markdown documents in the repository root

Copyright 2026 The OpenVDL Authors.
