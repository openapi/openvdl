# OpenVDL Exploration Diary

This directory is the exploration diary for world facts that may later
become part of maintained OpenVDL validator semantics.

## Purpose

Modern LLM and agentic tooling makes it possible to run structured
explorations over real-world domains:

- numbering plans
- registry behavior
- provider policy changes
- allocation rules
- document formats
- identifier lifecycles

Those explorations may surface facts that matter for validation.

OpenVDL should represent the final semantic facts inside validator
documents themselves. This directory serves a different purpose:

- record the exploration process
- keep hypotheses and intermediate findings visible
- preserve research rounds
- track how a discovered fact moved from exploration into validator
  semantics

In short:

- validator documents carry the canonical semantic facts
- the exploration diary carries the discovery history

Both are useful, but they are not the same thing.

## Why This Matters

Without an exploration diary, teams tend to lose:

- failed hypotheses
- discarded assumptions
- partial observations
- the reason a fact was trusted
- the sequence of discovery steps

For a maintained validator library, this matters because some rules are
not obvious from standards alone. They emerge from ongoing observation
of the world.

## What Belongs Here

This directory should contain:

- exploration session notes
- research round logs
- hypothesis lists
- candidate facts under review
- links from exploration rounds to validator revisions

This directory should not be the sole place where a validation-relevant
fact exists. Once a fact materially affects validation behavior, its
essential semantic form should be embedded in the relevant OpenVDL
document.

## Suggested Workflow

1. start an exploration round
2. capture the domain, goal, and hypothesis
3. record evidence, contradictions, and confidence
4. decide whether a fact is strong enough to affect validation
5. embed the resulting fact into the validator semantics
6. link the validator change back to the exploration round

## File Layout

- `index.md`: top-level map of exploration areas and rounds
- `rounds/`: individual exploration rounds
- `domains/`: optional domain summaries over time

## Relationship With OpenVDL Semantics

The intended model is:

- exploration diary = research and discovery layer
- OpenVDL document facts = semantic and implementation-facing layer

If these diverge, the OpenVDL document is the source of truth for
validation behavior, and the diary explains how that truth was reached.
