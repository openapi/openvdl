> Original seed notes for OpenVDL (v0.1). Kept for history; the current
> material lives in [README.md](README.md) and [docs/](docs).

# OpenVDL - Open Validation Description Language

**Version:** 0.1 (Draft)

---

# Mission

OpenVDL (Open Validation Description Language) is an open specification for describing data validation rules in a portable, machine-readable and implementation-independent format.

Today, validation logic is almost always embedded inside source code. Every programming language, framework and application reimplements the same validators repeatedly:

* email
* IBAN
* ISBN
* UUID
* VAT numbers
* fiscal identifiers
* phone numbers
* postal codes
* business identifiers
* banking identifiers
* and thousands of domain-specific formats.

This approach leads to duplicated implementations, inconsistent behavior across platforms, maintenance costs and incompatibilities between ecosystems.

OpenVDL proposes a different model.

Instead of implementing validators, software interprets validator descriptions.

OpenVDL describes validation logic without binding it to a programming language.

The validator becomes data.

The validation engine becomes universal.

---

# Vision

Write once.

Validate everywhere.

Every language.

Every platform.

Every runtime.

---

# Design Principles

## Declarative

Validation rules are described, not programmed.

## Portable

The same validator can be interpreted by any compliant implementation.

## Language Independent

No dependency on PHP, Java, Rust, Go, Python, JavaScript or any specific runtime.

## Extensible

New validation algorithms can be introduced without modifying existing validators.

## Deterministic

Given identical input and validator definitions, every implementation must produce identical results.

## Versionable

Validators are versioned independently from software implementations.

## Human Readable

Specifications should remain understandable by developers.

---

# Scope

OpenVDL describes validation logic for structured values.

Examples include:

* Email addresses
* URLs
* UUIDs
* IP addresses
* IBAN
* BIC
* ISBN
* Credit Cards
* National identifiers
* VAT numbers
* Postal codes
* Vehicle Identification Numbers
* Domain names
* Phone numbers
* Product codes

It is equally suitable for organization-specific validation policies.

---

# Validation Model

A validator is composed of one or more validation stages.

Example:

Email

↓

RFC Syntax

↓

Provider Policy

↓

Organization Policy

↓

Accepted

Each stage contributes additional constraints.

---

# Rule Categories

OpenVDL supports several categories of rules.

## Structural Rules

Length

Character sets

Encoding

Unicode support

Normalization

Whitespace

Allowed symbols

Forbidden symbols

## Pattern Rules

Regular expressions

Prefixes

Suffixes

Character classes

Token ordering

## Numeric Rules

Ranges

Modulo

Checksums

Digit verification

Parity

## Algorithmic Rules

Luhn

Mod97

ISO algorithms

National algorithms

Custom algorithms

## Conditional Rules

If

Else

Switch

Country dependent

Provider dependent

Version dependent

## Composite Rules

AND

OR

NOT

Nested validators

Referenced validators

## External Rules

DNS lookup

HTTP lookup

Certificate verification

Public key verification

Directory lookup

Remote policy retrieval

---

# Validator Composition

Validators may import other validators.

Example

Email

extends RFC5322

adds Gmail policy

adds Company policy

Each validator remains reusable.

---

# Provider Policies

One major objective is allowing providers to publish additional validation rules.

Example

gmail.com

forbid underscore

ignore dots

support plus addressing

Another provider may expose different constraints.

Applications no longer need provider-specific code.

---

# Distribution

Validators should be distributable independently.

Possible mechanisms

* Git repositories
* Package managers
* DNS records
* Well-known URLs
* Registry services
* Enterprise repositories

Example

/openvdl/email

/openvdl/iban

/openvdl/isbn

---

# Deterministic Validation

Every compliant implementation must return

VALID

INVALID

or

ERROR

No implementation-specific behavior should exist.

---

# Error Reporting

Validation engines should expose structured diagnostics.

Example

Rule failed

Expected

Maximum length 64

Actual

Length 71

Location

local-part

Rule identifier

email.local.maxLength

---

# Versioning

Validators are immutable.

Breaking changes require new versions.

Applications may select validator versions explicitly.

---

# Security

OpenVDL validators must never execute arbitrary code.

Validator descriptions are declarative.

Implementations remain responsible for resource limits.

Network operations should be optional.

Recursive validators must be bounded.

---

# Future Extensions

Digital signatures

Validator registries

Capability negotiation

Semantic validation

Policy inheritance

Localization

Streaming validation

Incremental validation

AI-assisted validator generation

---

# Example Applications

Validate an email.

Validate an Italian fiscal code.

Validate an IBAN.

Validate a VAT number.

Validate a vehicle VIN.

Validate an ISBN.

Validate a company's internal employee identifier.

Validate a blockchain address.

Validate industrial serial numbers.

---

# Ecosystem

Possible future projects

OpenVDL Specification

OpenVDL Registry

OpenVDL CLI

OpenVDL Reference Interpreter

OpenVDL Test Suite

OpenVDL Playground

OpenVDL Conformance Tests

Language SDKs

PHP

Rust

Go

Python

JavaScript

Java

C#

C

Swift

Kotlin

---

==========================================================
Internet-Draft (RFC Draft)
==========================

Title

Open Validation Description Language (OpenVDL)

Abstract

This document defines the Open Validation Description Language (OpenVDL), a declarative language for describing validation rules independently of implementation languages. OpenVDL enables interoperable validation of structured values by expressing constraints, algorithms, conditional rules and composition using a standardized, portable specification.

Status of This Memo

This document is an Internet-Draft.

It is intended for discussion and experimentation.

No implementation is required to conform at this stage.

Introduction

Validation logic is traditionally embedded within application source code.

This practice duplicates effort across ecosystems and often produces inconsistent implementations.

OpenVDL introduces a portable representation of validation semantics.

Instead of implementing validators repeatedly, applications implement a single OpenVDL interpreter.

Terminology

Validator

A complete validation specification.

Rule

A single validation constraint.

Constraint

A property that must hold.

Validation Engine

Software capable of interpreting OpenVDL.

Registry

Repository of published validators.

Requirements Language

The key words "MUST", "SHOULD", "MAY", "MUST NOT" and "SHOULD NOT" are to be interpreted as described in RFC 2119.

Architecture

Validator

↓

Parser

↓

Interpreter

↓

Validation Result

Conformance

An implementation conforms if it

* correctly parses OpenVDL documents;
* evaluates all mandatory rule types;
* produces deterministic results;
* reports structured validation diagnostics.

Security Considerations

Validators MUST NOT execute arbitrary code.

Recursive references MUST be detected.

External lookups SHOULD be sandboxed.

Denial-of-service protections SHOULD exist.

IANA Considerations

Future versions may request media types such as

application/openvdl+yaml

application/openvdl+json

or

application/openvdl+xml

This document makes no current IANA requests.

References

RFC 2119

RFC 5234 (ABNF)

RFC 5321

RFC 5322

RFC 6531

ISO 13616 (IBAN)

ISO 7064

Acknowledgments

The OpenVDL community and all contributors dedicated to making validation portable, deterministic and implementation independent.
