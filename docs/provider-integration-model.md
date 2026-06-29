# OpenVDL Provider Integration Model

## Purpose

OpenVDL should not describe only local validation logic.

Some validations depend on external truth sources. In those cases the
system is not only evaluating syntax or algorithms, but also consulting
an authoritative provider.

Examples:

- VAT validation against official registries
- business identifier checks against business registries
- account or banking checks against external systems
- validation services exposed by specialized third-party providers

This means OpenVDL may need to describe both:

- validation logic
- provider interaction contracts

## Core Expansion of Scope

The scope of OpenVDL may need to include:

1. local rule-based validation
2. provider-backed validation
3. request/response normalization across heterogeneous providers

That makes OpenVDL closer not only to a validator language, but also to
an interoperability layer for validation services.

## Two Architectural Models

### Model A: Providers conform directly to OpenVDL

In this model, providers expose request and response formats that follow
OpenVDL directly.

Advantages:

- clean interoperability
- simpler execution model
- consistent diagnostics and result semantics

Disadvantages:

- low adoption probability for existing providers
- difficult migration path
- unrealistic for many established truth-source systems

### Model B: OpenVDL defines an adapter layer

In this model, providers keep their native APIs, and OpenVDL defines how
to adapt those APIs into OpenVDL semantics.

Advantages:

- much more realistic adoption path
- allows integration with existing APIs
- does not require providers to redesign their interfaces

Disadvantages:

- more complexity in OpenVDL
- adapter semantics must be standardized carefully
- risk of inconsistent mappings if underspecified

## Recommended Direction

The strongest practical position is:

- OpenVDL should define its own validation semantics
- OpenVDL should support native provider conformance
- OpenVDL should also define an adapter model for third-party APIs

In practice, the adapter model is likely to matter more in the early
ecosystem because most external truth sources already expose existing
interfaces.

## What OpenVDL May Need to Describe

For provider-backed validation, OpenVDL may need formal structures for:

- request payload shape
- field mapping from input to provider request
- authentication requirements
- transport metadata
- response payload shape
- mapping of provider fields into OpenVDL result states
- mapping of provider diagnostics into OpenVDL diagnostics
- timeout and retry behavior
- trust, provenance, and freshness metadata

## Semantic Distinction

OpenVDL should distinguish clearly between:

- syntactic validation
- algorithmic validation
- policy validation
- truth-source validation

This distinction matters because a value can be:

- syntactically valid
- algorithmically valid
- but not confirmed by an authoritative source

That is a different class of result than a plain regex failure.

## Request and Response Contract

OpenVDL may eventually need a provider contract model such as:

- provider input schema
- provider output schema
- mapping to `VALID`, `INVALID`, `ERROR`
- mapping to structured diagnostics

This can be native or adapted.

## Adapter Language

If OpenVDL takes the adapter route, it should formalize how to describe:

- endpoint location
- HTTP method or transport type
- request templating or field binding
- response extraction
- status mapping
- error mapping
- authentication references

The key design constraint is that the adapter model must remain
declarative. OpenVDL should not turn into a scripting language.

## Open Questions

- Should provider-backed validation be part of the core spec or an extension profile?
- Should provider contracts be transport-agnostic or HTTP-first?
- Should OpenVDL define freshness semantics for truth-source data?
- How should rate limits and retries be represented?
- Can one validator aggregate both local and provider-backed stages cleanly?

## Recommended Next Step

The next concrete step is to define whether provider integration belongs
to:

- the OpenVDL core model
- an official extension profile
- or a separate companion specification

My current recommendation is:

- core OpenVDL defines the semantic hooks
- an extension profile defines provider contracts and adapter mappings

That keeps the base language clean while still making truth-source
validation a first-class part of the ecosystem.
