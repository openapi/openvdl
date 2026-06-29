# OpenVDL Maintained Validators

This directory is intended to host validators maintained by the OpenVDL
project itself.

The purpose is not only to collect validator definitions, but to build a
curated validator knowledge base that evolves as real-world rules,
constraints, and provider behavior change over time.

Examples of changes that may matter:

- numbering plan changes
- provider policy changes
- identifier allocation changes
- registry behavior changes
- deprecations of previously accepted values

## Structure

- `openvdl.yml`: repository-level entry point for curated validators
- domain folders such as `email/`, `phone/`, `tax/`, `banking/`
- `facts/`: supporting notes about world facts that motivate validator
  updates

## Important Principle

Facts discovered over time should be captured explicitly and traceably.

A validator change should ideally be linked to:

- a documented observation
- a source or rationale
- a date or revision note

This helps distinguish:

- the validator definition
- the motivation for the validator definition

## Current Status

This directory is an initial scaffold for the maintained validator
library. The final canonical layout may evolve once the OpenVDL data
model and registry model are more precise.
