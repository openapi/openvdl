# Contributing to OpenVDL

OpenVDL is a draft specification. Its most useful contributions right now are feedback on
the draft and new validators written as OpenVDL documents.

## Ways to contribute

- **Comment on the specification.** Open an issue about anything unclear, missing or
  wrong in [RFC-OpenVDL.txt](RFC-OpenVDL.txt) or [docs/](docs). The open questions in
  [ROADMAP.md](ROADMAP.md) are a good place to start.
- **Write a validator.** Describe a format you know well (postal code, national identifier,
  product code...) as an OpenVDL YAML document. See [examples/](examples) for the shape.
- **Contribute to the maintained library.** Add validators under [validators/](validators)
  and reference them from the namespace entry point.
- **Record facts.** If a validator depends on a real-world fact (a numbering plan, a registry
  rule), record it in the validator's `facts` section, with its provenance and effective date.
- **Build an engine.** Implementations in any language are welcome. [libopenvdl/](libopenvdl)
  is an early C scaffold.

## Guidelines for validator documents

- One validator per file, with `openvdl`, `id`, `version`, `name` and `description`.
- Give every rule a stable, descriptive `id` (e.g. `iban.mod97`). Rule ids appear in diagnostics.
- Published versions are immutable. A breaking change needs a new version.
- Prefer `extends`, `imports` and `ref` over copying rules from another validator.
- Cite the standard or source you relied on in `metadata.references` or in `facts`.
- Check that the file is valid YAML before opening a pull request.

## Licensing of contributions

By contributing you agree that code and validator documents are licensed under the
[Apache License 2.0](LICENSE), and specification and documentation text under
[CC BY 4.0](LICENSE-SPEC). See the License section of the [README](README.md).

## Commits and pull requests

- Keep each pull request focused on one change.
- Commit messages follow [Conventional Commits](https://www.conventionalcommits.org/),
  e.g. `docs(openvdl): clarify match semantics` or `feat(validators): add Italian VAT`.
