# libopenvdl

`libopenvdl` is an early C reference runtime scaffold for OpenVDL.

It is intentionally small. The goal is to exercise the stable parts of
the model without freezing unresolved parts of the specification too
early.

## Scope

This scaffold currently provides:

- a minimal OpenVDL result model
- validator, stage, rule, and diagnostic structures
- a local in-memory evaluator
- focused support for simple string-based rules
- unit tests

This scaffold does not yet provide:

- YAML or JSON parsing
- file loading
- provider-backed validation
- external lookup adapters
- full composition semantics
- `extends`, `imports`, `ref`, `match`, or `cases`

## Current Rule Support

- `minLength`
- `maxLength`
- `containsChar`
- `domainEquals`
- `partMinLength`
- `partMaxLength`

The current intent is to validate the runtime shape of OpenVDL, not to
declare the specification complete.

## Build

```sh
make -C libopenvdl
```

## Test

```sh
make -C libopenvdl test
```
