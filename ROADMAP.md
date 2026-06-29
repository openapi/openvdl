# ROADMAP

This file tracks the working evolution of OpenVDL.

It is intentionally practical and can change as the language becomes clearer.

## Current Direction

The current foundation of OpenVDL is:

- OpenVDL defines a validator data model, not a single implementation
- validators must be reusable, extendable, and composable
- a root document may act as an aggregator of validators
- conditional orchestration is a first-class concern
- YAML is convenient, but the long-term model should remain serialization-independent

## Current Priorities

- [x] establish project README
- [x] write draft RFC-style specification
- [x] add plain-text RFC in root
- [x] define serialization position for YAML and JSON
- [x] define composition as a foundational principle
- [x] introduce `match` / `cases` as multi-branch dispatch
- [x] add initial composed validator examples
- [x] define the problem space for provider-backed validation and truth-source integration
- [x] add an initial `libopenvdl` C runtime scaffold
- [x] add an initial maintained validator library scaffold with a single `openvdl.yml` entry point
- [x] add an exploration diary scaffold for world-fact discovery rounds
- [ ] define the canonical OpenVDL document model
- [ ] define precise semantics of `extends`
- [ ] define precise semantics of `imports` and `ref`
- [ ] define evaluation semantics for `allOf`, `anyOf`, `oneOf`, `not`
- [ ] define evaluation semantics for `if/then/else`
- [ ] define evaluation semantics for `match/cases/default`
- [ ] define validator identifier and version reference format
- [ ] define diagnostics model and error codes
- [ ] define capability model for external lookups
- [ ] define request/response contract model for validation providers
- [ ] define adapter model for third-party validation APIs
- [ ] define trust and truth-source semantics
- [ ] define recursion and cycle handling
- [ ] define normalization pipeline semantics
- [ ] define conformance levels for implementations
- [ ] define JSON serialization and JSON Schema
- [ ] align `libopenvdl` with the canonical data model once the shape is fixed
- [ ] define the structure and governance model of the maintained validator library
- [ ] define first-class fact semantics inside OpenVDL documents
- [ ] define how embedded facts are linked to validator revisions
- [ ] define how exploration rounds link to semantic facts and validator revisions

## Proposed Near-Term Work

### 1. Canonical Data Model

Write a document that defines the required top-level sections of an OpenVDL document, for example:

- `openvdl`
- `id`
- `version`
- `input`
- `imports`
- `extends`
- `compose`
- `stages`
- `result`
- `metadata`

### 2. Semantic Distinctions

Make these boundaries explicit:

- `extends` adds constraints to a base validator
- `imports` declares dependencies
- `ref` invokes or references imported validators
- `compose` orchestrates validator logic

### 3. Aggregator Model

Specify that an entry-point document may behave primarily as:

- a validator
- an orchestration root
- a dispatch layer over a validator library

### 4. Match Semantics

Decide early whether `match` should operate on:

- a named field
- a path expression
- a computed selector
- the output of earlier stages

Also define:

- case ordering
- first-match vs exact-match behavior
- default behavior when no case matches

### 5. Example Library

Build a small but representative validator set:

- base email
- provider-specific email policy
- organization-specific email extension
- phone validator
- VAT by country dispatcher
- generic user identifier aggregator

### 5b. Maintained Validator Library

Define how the project-managed validator library should be organized:

- single entry point such as `validators/openvdl.yml`
- namespace layout by domain
- embedded fact representation inside validator documents
- traceability from embedded fact to validator revision

### 5c. Exploration Diary

Define how the exploration diary should work:

- round naming and lifecycle
- hypothesis recording
- confidence tracking
- linkage from exploration round to embedded semantic fact
- linkage from semantic fact to validator revision

### 6. Provider Integration Model

Decide whether OpenVDL should standardize:

- a native provider protocol
- an adapter language for wrapping third-party APIs
- or both

This includes formalizing:

- request payload mapping
- response payload mapping
- result normalization
- trust/source metadata
- failure and timeout semantics

## Proposed Longer-Term Work

- registry and distribution model
- provider conformance profile
- adapter runtime and mapping library
- digital signatures for published validators
- test vectors and conformance suite
- reference interpreter
- CLI and playground
- machine-readable schema artifacts
- mature `libopenvdl` from scaffold into a reference implementation
- mature the maintained validator library into a curated public catalog
- mature the exploration diary into a reusable fact-discovery workflow

## Open Questions

- Should `extends` support one base validator or multiple base validators?
- Should `ref` be allowed directly inside stages, or only inside composition blocks?
- Should `match` be able to dispatch on context metadata as well as input fields?
- Should result diagnostics accumulate across failed branches in `anyOf` and `oneOf`?
- Should provider policies be modeled as ordinary validators or a special policy category?
- Should OpenVDL require providers to conform directly, or should adapters be the primary integration path?
- How should OpenVDL distinguish syntactic validation from truth-source validation?
- How should provider trust, provenance, and freshness be represented?
- What is the canonical fact model for world knowledge inside OpenVDL documents?
- Should curated validator libraries be part of the OpenVDL core ecosystem or a separate maintained distribution?
- What is the minimum link model between exploration round, embedded fact, and validator revision?

## Suggested Next Step

Write a dedicated `docs/data-model.md` that fixes the canonical shape of an OpenVDL document before adding too many more examples.
