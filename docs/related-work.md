# Related Work and Ecosystem Alignment

## Purpose

OpenVDL is not the first attempt to move validation logic out of code. This document
records the closest related work, what OpenVDL can learn or reuse from it, and which parts of
OpenVDL appear to be distinctive.

The survey was done on 2026-09-28. Star counts and activity dates reflect that day.

## Landscape

| Project / standard | What it is | Overlap | Difference from OpenVDL |
|---|---|---|---|
| [LIVR](https://livr-spec.org/) | Language-independent validation rules as JSON, with engines in many languages | High | Generic structural rules only: no checksums, identifier library, versioning or facts. The spec repository has not changed since 2022. |
| [Microsoft Purview sensitive information types](https://learn.microsoft.com/en-us/purview/sit-regex-validators-additional-checks) | XML rule packages with declarative checksum, Luhn and date validators | High for "checksums as data" | Proprietary and tied to data loss prevention; not a portable open specification. |
| [JSON Schema 2020-12](https://json-schema.org/draft/2020-12/json-schema-validation) | Structural schema language with composition (`allOf`, `anyOf`, `oneOf`, `not`, `if/then/else`, `$ref`) | Medium | `format` is an annotation by default, and format names such as `iban` are opaque: the schema does not define what a valid value is. |
| [CEL](https://github.com/google/cel-spec) and [Protovalidate](https://protovalidate.com/) | Portable, non-Turing-complete expression language; cross-language Protobuf validation built on it with a conformance suite | Medium (expression layer) | Not a catalog of real-world identifiers; Protovalidate is tied to Protobuf. |
| [libphonenumber](https://github.com/google/libphonenumber) | Phone number parsing and validation driven by metadata (`PhoneNumberMetadata.xml`) | High for phone numbers | Covers a single domain. |
| [python-stdnum](https://arthurdejong.org/python-stdnum/) | Validation of 200+ identifier formats (VAT, tax IDs, IBAN, ISBN...) | High for coverage | Rules are Python code; only reference tables are data. |
| [SWIFT IBAN Registry](https://www.swift.com/standards/data-standards/iban-international-bank-account-number) | Authoritative IBAN structures per country (ISO 13616) | High for data | Data only, no rule language or engine. |

Other related but lower-overlap work: CDDL (RFC 8610), JSON Type Definition (RFC 8927),
SHACL and Schematron, configuration languages such as CUE and Pkl, policy languages such as
OPA/Rego and Cedar, and dataset-level data quality tools such as Great Expectations and Soda.

## What Appears Distinctive

We found no open specification that combines the following:

1. **Facts as validator semantics.** Real-world knowledge behind a rule (numbering plans,
   registry policies), recorded with provenance, confidence and effective date inside the
   validator. In existing libraries this knowledge lives only in commit messages or comments.
2. **Provider-backed validation contracts** for external truth sources (for example VAT
   registries) in the same document model as local rules.
3. **An open, curated and versioned library of real-world identifiers as data**, with
   dispatch such as VAT by country.
4. The combination of the above for identifier-grade validation, as opposed to generic
   structural validation.

## Alignment Direction

OpenVDL should build on existing work instead of competing with it.

### Expressions: adopt CEL

OpenVDL should not invent its own expression language. Where a rule needs a custom
predicate, OpenVDL should consider CEL: it is portable, safe, non-Turing-complete, and
already has several independent implementations.

### JSON Schema: complement, don't replace

- Reuse JSON Schema names and semantics for composition keywords where they overlap.
- Define a bridge so that a JSON Schema `format` can refer to an OpenVDL validator, for
  example `format: "openvdl:iban@1"`. OpenVDL then provides the definition behind a format
  name that JSON Schema leaves opaque.
- Describe the structure of OpenVDL documents with a JSON Schema (already on the roadmap).

### Authoritative data: generate, don't copy

- Generate IBAN validators from the SWIFT IBAN Registry.
- Generate phone validators from libphonenumber metadata (Apache-2.0).
- Record the source and its version as facts in the generated validators.
- Use python-stdnum's test cases as a coverage benchmark. Its code is LGPL and should not
  be copied.

### Checksums: parametric model

Beyond named algorithms (`mod97`, `luhn`), a generic weighted-checksum rule (weights,
modulus, check-digit position, character-to-number mapping) could describe many national
identifiers without a named algorithm for each. Microsoft Purview's checksum validator is a
useful reference model.

### Conformance suite

Shared test vectors (input, validator, expected `VALID` / `INVALID` / `ERROR`) are what make
"any engine, same result" verifiable, as Protovalidate's conformance suite does.

## Naming Note

"VDL" is also used by older projects, such as the Vienna Definition Language. An academic
library called "Open Verification Developer Library" (OpenVDL) existed inside JTLV around 2010.
To avoid ambiguity, documents should spell out "Open Validation Description Language" at
first mention.
