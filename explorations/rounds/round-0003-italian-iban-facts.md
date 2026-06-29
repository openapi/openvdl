# Round 0003 - Italian IBAN Facts

Status: exploratory

## Goal

Explore interesting facts about Italian IBANs, especially around:

- the meaning of prefixes like `IT80E`
- whether the letter after the two digits is fixed
- whether an IBAN starting with `IT90` can exist

## Questions

1. In an Italian IBAN such as `IT80E...`, is the `E` always the same?
2. Can `IT90...` exist for a valid Italian IBAN?
3. Which parts of the prefix are structural, and which are computed?

## Baseline Structure

For Italy, the IBAN has:

- `IT`: country code
- two numeric check digits
- a 23-character Italian BBAN

Within the Italian BBAN, the first character is the national control
character usually called `CIN`, followed by:

- ABI
- CAB
- account number

## Findings

### 1. `IT80E` is not a single fixed prefix

The string `IT80E` contains two different control layers:

- `80` = IBAN check digits
- `E` = Italian national control character (`CIN`)

These are computed for the specific BBAN. They are not fixed constants
for all Italian IBANs.

Conclusion:

- `E` is not always the same
- `80` is not always the same
- the apparent prefix `IT80E` is just one concrete outcome for one
  specific Italian account structure

### 2. The `CIN` letter varies

Local computation over Italian-style BBAN values produced multiple valid
`CIN` letters, including:

- `A`
- `B`
- `C`
- `D`
- `E`
- `F`
- `G`
- `H`
- `T`
- `U`

This is strong evidence that the `CIN` is a computed control character,
not a fixed literal such as always `E` or always `X`.

### 3. `IT90` can exist

Using the Italian `CIN` computation plus the standard IBAN checksum
algorithm, a syntactically valid Italian IBAN with `IT90` was derived:

`IT90H0542811101000000000029`

This supports the conclusion that `90` is a possible check-digit pair
for Italian IBANs.

Important note:

- this means "algorithmically valid under IBAN and Italian BBAN control rules"
- it does not prove that the referenced bank account is real or active

### 4. A useful semantic distinction emerges

Italian IBAN validation naturally splits into at least three layers:

1. structural validation
2. national control validation
3. account/truth-source validation

That is useful for OpenVDL because it suggests separate validator
stages:

- country format stage
- Italian `CIN` stage
- IBAN checksum stage
- optional provider or truth-source stage

## Derived Examples

### Common example

`IT60X0542811101000000123456`

This is a standard example often used in IBAN documentation.

### Derived `IT90` example

`IT90H0542811101000000000029`

This was derived locally by applying:

- Italian `CIN` control computation
- IBAN modulo-97 checksum computation

## Implications for OpenVDL

Potential validator facts worth encoding semantically:

- in Italy the BBAN includes a national control character (`CIN`)
- the `CIN` is computed from the domestic banking coordinates
- the IBAN check digits and the national `CIN` are distinct control layers
- a prefix such as `IT80E` must not be treated as a fixed literal pattern
- an IBAN can be structurally and algorithmically valid without proving
  that the account exists

## Sources

Primary exploration inputs:

- repository-local computation using the Italian control-character logic
  and standard IBAN checksum logic

Secondary references used for structural orientation:

- https://it.wikipedia.org/wiki/Coordinate_bancarie
- https://it.wikipedia.org/wiki/International_Bank_Account_Number

## Confidence

Medium to high.

Reason:

- the split between country code, check digits, and BBAN is standard
- the variability of the `CIN` and the existence of an `IT90` example
  were confirmed by direct computation
- the references used for quick structure confirmation are secondary,
  not the strongest possible primary standards source

## Next Step

Translate these findings into:

- a dedicated Italian IBAN exploration fact block
- a future OpenVDL validator model with separate stages for:
  - structure
  - national control
  - IBAN checksum
  - truth-source validation
