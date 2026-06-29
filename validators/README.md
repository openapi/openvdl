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
- embedded `facts` sections inside validator documents where world
  knowledge affects validation behavior

## Important Principle

Facts discovered over time should be captured explicitly, traceably, and
inside the semantic model of OpenVDL documents.

A validator change should ideally be linked to embedded facts carrying:

- a factual statement
- a source or rationale
- a confidence indicator
- a date or revision note

Separate notes may still exist for editorial context, but they are not
the canonical semantic carrier of validation facts.

## Current Status

This directory is an initial scaffold for the maintained validator
library. The final canonical layout may evolve once the OpenVDL data
model and registry model are more precise.
