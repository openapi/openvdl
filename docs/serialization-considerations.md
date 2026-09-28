# OpenVDL Serialization Considerations

## Premise

An important choice for OpenVDL is to distinguish between:

- the **data model** of the language
- its **concrete serialization**

This distinction matters a lot. If OpenVDL is defined directly as "a YAML format", the standard inherits the strengths and limits of YAML. If OpenVDL is instead defined as an abstract semantic model, then YAML, JSON and other formats become simple representations of the same content.

The recommended choice is:

- **OpenVDL should not be YAML**
- **OpenVDL should be an abstract data model**
- **YAML and JSON should be official serializations of the model**

In RFC wording:

> This document defines the OpenVDL data model. YAML and JSON are
> serialization formats of that model.

## Why YAML is a natural choice

YAML is a natural choice for a project like OpenVDL, but it is neither
automatic nor free of costs.

OpenVDL aims to describe validators that are readable by humans, easy
to discuss in a repository, and simple to share across different
implementations. From this point of view YAML has several practical
advantages.

## YAML as a metalanguage: arguments in favor

### 1. Human readability

For a specification like OpenVDL it is important that a validator for
email, IBAN or VAT numbers can be read even without specialized
tooling.

Example:

```yaml
rules:
  - type: length
    max: 34
  - type: checksum
    algorithm: mod97
```

This is immediately readable in reviews, issue trackers,
documentation and public repositories.

### 2. Widespread familiarity

YAML is already very familiar to developers and operators thanks to
tools and standards such as:

- OpenAPI
- GitHub Actions
- Kubernetes
- Docker Compose
- many CI/CD systems

Using a syntax people already know lowers the barrier to entry.

### 3. Good fit for nested structures

OpenVDL will probably have:

- rules
- stages
- conditions
- composition between validators
- metadata

YAML represents nested structures well without much syntactic noise.

### 4. Great for examples and collaboration

For teaching examples, documentation, specification drafts and
community contributions, YAML is often better suited than JSON,
especially in the early phases of a project.

## YAML as a metalanguage: arguments against

### 1. Semantic ambiguities

YAML has a history of parsing that is not perfectly uniform across
parsers, versions and libraries.

Classic examples:

- `yes`
- `no`
- `on`
- `off`
- `01`

can be interpreted in unexpected ways depending on the parser or the
YAML profile in use.

For a standard that aims at strong determinism, this is a real
problem, not a theoretical one.

### 2. Less rigid than JSON

YAML is very flexible, but for that very reason it is harder to
constrain rigorously and uniformly, especially if the goal is to
reduce differences in interpretation between implementations to zero.

### 3. Indentation errors and invisible problems

Whitespace, indentation and small formal mistakes can produce problems
that are hard to spot, especially in long or complex files.

### 4. Perception as a "soft format"

In an RFC or a technical standard, YAML may be perceived as too
permissive if the goal is to guarantee deterministic and strictly
interoperable behavior.

## Alternatives to consider

## JSON

### Advantages

- more rigid
- more universal
- easier to parse deterministically
- well suited to automated tooling

### Disadvantages

- less readable for humans
- noisier in example documents

Example:

```json
{
  "rules": [
    { "type": "length", "max": 34 },
    { "type": "checksum", "algorithm": "mod97" }
  ]
}
```

## JSON Schema

JSON Schema is not a direct alternative to OpenVDL as a language, but
it is a very useful tool for describing and validating the structure
of OpenVDL documents.

Recommended use:

- OpenVDL data model as the standard
- YAML and JSON as serializations
- JSON Schema to formally validate the structure

## TOML

### Advantages

- simpler than YAML
- readable
- less ambiguous

### Disadvantages

- less natural for deeply nested structures
- less expressive for some complex composition cases

TOML can be pleasant for configuration, but it is less suited as the
primary serialization of an articulated description language.

## S-expressions / Lisp-like syntax

Example:

```lisp
(and
  (length max 34)
  (checksum mod97))
```

### Advantages

- very formal
- easy to parse
- great for canonical representations

### Disadvantages

- unfamiliar to most developers
- probably hard to get adopted as the main syntax

## Custom DSL

Example:

```text
length max 34
checksum mod97
```

### Advantages

- maximum adherence to the domain
- very compact syntax

### Disadvantages

- requires dedicated parsers
- requires formatters, tooling, syntax highlighting and validators
- greatly increases the initial cost of the standard

For an early phase of the project, a custom DSL looks like an
unjustified cost.

## Recommendation

The most solid recommendation is this:

### 1. OpenVDL must define an abstract semantic model

The standard should not coincide with a single concrete syntax.

### 2. YAML should be an official human-oriented serialization

YAML is great for:

- examples
- documentation
- manual editing
- collaboration in repositories

### 3. JSON should be an official machine-oriented serialization

JSON is great for:

- rigorous parsers
- tool-to-tool interchange
- embedded implementations
- automated pipelines

### 4. JSON Schema should be used for structural validation

This makes it possible to rigorously constrain the shape of documents,
even when the chosen serialization is YAML.

### 5. The file extension can remain conventional

Possible conventions:

- `openvdl.yaml`
- `openvdl.json`
- possibly `.ovdl` as an ecosystem extension

## Final suggestion

The architecturally strongest position for OpenVDL is:

- do not tie the standard to YAML
- use YAML as a convenient syntax
- keep the model independent of the format

In practice:

- **YAML for humans**
- **JSON for machines**
- **JSON Schema for structural validation**

This choice makes OpenVDL more robust as a standard, more
interoperable across implementations, and less exposed to the specific
limits of a single serialization format.
