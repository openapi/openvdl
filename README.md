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

In that sense, OpenVDL is closer to what OpenAPI did for APIs than to a traditional validation library.

## Repository Structure

- [docs/internet-draft.md](docs/internet-draft.md): RFC-style Internet-Draft for the format
- [docs/specification.md](docs/specification.md): practical specification overview
- [examples/email.yaml](examples/email.yaml): example email validator
- [examples/iban.yaml](examples/iban.yaml): example IBAN validator

## Design Principles

- Declarative
- Portable
- Language independent
- Extensible
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

## Status

This repository currently contains a draft specification intended for discussion and experimentation. It is not yet a final standard.
