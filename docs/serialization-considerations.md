# OpenVDL Serialization Considerations

## Premessa

Una scelta importante per OpenVDL e' distinguere tra:

- il **data model** del linguaggio
- la sua **serializzazione concreta**

Questa distinzione conta molto. Se OpenVDL viene definito direttamente come "un formato YAML", allora lo standard eredita pregi e limiti di YAML. Se invece OpenVDL viene definito come un modello semantico astratto, allora YAML, JSON e altri formati diventano semplici rappresentazioni dello stesso contenuto.

La scelta raccomandata e':

- **OpenVDL non dovrebbe essere YAML**
- **OpenVDL dovrebbe essere un data model astratto**
- **YAML e JSON dovrebbero essere serializzazioni ufficiali del modello**

In formulazione RFC:

> This document defines the OpenVDL data model. YAML and JSON are
> serialization formats of that model.

## Perche' YAML e' una scelta naturale

YAML e' una scelta naturale per un progetto come OpenVDL, ma non e'
automatica ne' priva di costi.

OpenVDL vuole descrivere validatori leggibili da umani, facilmente
discutibili in una repo, e semplici da condividere tra implementazioni
diverse. Da questo punto di vista YAML ha diversi vantaggi pratici.

## YAML come metalinguaggio: punti a favore

### 1. Leggibilita' umana

Per una specifica come OpenVDL e' importante che un validatore per
email, IBAN o VAT number possa essere letto anche senza tooling
specializzato.

Esempio:

```yaml
rules:
  - type: length
    max: 34
  - type: checksum
    algorithm: mod97
```

Questo e' immediatamente leggibile anche in review, issue tracker,
documentazione e repository pubbliche.

### 2. Familiarita' diffusa

YAML e' gia' molto familiare a sviluppatori e operatori per via di
strumenti e standard come:

- OpenAPI
- GitHub Actions
- Kubernetes
- Docker Compose
- molti sistemi CI/CD

Usare una sintassi gia' nota abbassa la barriera d'ingresso.

### 3. Buona resa per strutture annidate

OpenVDL probabilmente avra':

- regole
- stage
- condizioni
- composizione tra validatori
- metadata

YAML rappresenta bene strutture annidate senza troppo rumore sintattico.

### 4. Ottimo per esempi e collaborazione

Per esempi didattici, documentazione, draft di specifica e contributi
community, YAML e' spesso piu' adatto di JSON, soprattutto nelle prime
fasi di un progetto.

## YAML come metalinguaggio: punti contro

### 1. Ambiguita' semantiche

YAML ha una storia di parsing non perfettamente uniforme tra parser,
versioni e librerie.

Esempi classici:

- `yes`
- `no`
- `on`
- `off`
- `01`

possono essere interpretati in modi inattesi a seconda del parser o del
profilo YAML utilizzato.

Per uno standard che vuole determinismo forte, questo e' un problema
reale, non teorico.

### 2. Minore rigidita' rispetto a JSON

YAML e' molto flessibile, ma proprio per questo e' piu' difficile da
vincolare in modo rigoroso e uniforme, soprattutto se si vogliono
ridurre a zero le differenze di interpretazione tra implementazioni.

### 3. Errori di indentazione e problemi invisibili

Whitespace, indentazione e piccoli errori formali possono produrre
problemi difficili da individuare, specialmente in file lunghi o
complessi.

### 4. Percezione di "formato morbido"

In una RFC o in uno standard tecnico, YAML puo' essere percepito come
troppo permissivo se l'obiettivo e' garantire un comportamento
deterministico e strettamente interoperabile.

## Alternative da considerare

## JSON

### Vantaggi

- piu' rigido
- piu' universale
- piu' facile da parsare in modo deterministico
- molto adatto a tooling automatico

### Svantaggi

- meno leggibile da umani
- piu' rumoroso nei documenti di esempio

Esempio:

```json
{
  "rules": [
    { "type": "length", "max": 34 },
    { "type": "checksum", "algorithm": "mod97" }
  ]
}
```

## JSON Schema

JSON Schema non e' un'alternativa diretta a OpenVDL come linguaggio, ma
e' uno strumento molto utile per descrivere e validare la struttura dei
documenti OpenVDL.

Uso consigliato:

- OpenVDL data model come standard
- YAML e JSON come serializzazioni
- JSON Schema per validare formalmente la struttura

## TOML

### Vantaggi

- piu' semplice di YAML
- leggibile
- meno ambiguo

### Svantaggi

- meno naturale per strutture profondamente annidate
- meno espressivo per certi casi di composizione complessa

TOML puo' essere piacevole per configurazioni, ma meno adatto come
serializzazione primaria di un linguaggio descrittivo articolato.

## S-expression / sintassi Lisp-like

Esempio:

```lisp
(and
  (length max 34)
  (checksum mod97))
```

### Vantaggi

- molto formale
- facile da parsare
- ottimo per rappresentazioni canoniche

### Svantaggi

- poco familiare alla maggior parte degli sviluppatori
- probabilmente difficile da far adottare come sintassi principale

## DSL custom

Esempio:

```text
length max 34
checksum mod97
```

### Vantaggi

- massima aderenza al dominio
- sintassi molto compatta

### Svantaggi

- richiede parser dedicati
- richiede formatter, tooling, syntax highlighting e validatori
- aumenta di molto il costo iniziale dello standard

Per una fase iniziale del progetto, una DSL custom sembra un costo
ingiustificato.

## Raccomandazione

La raccomandazione piu' solida e' questa:

### 1. OpenVDL deve definire un modello semantico astratto

Lo standard non dovrebbe coincidere con una singola sintassi concreta.

### 2. YAML dovrebbe essere una serializzazione ufficiale orientata agli umani

YAML e' ottimo per:

- esempi
- documentazione
- editing manuale
- collaborazione in repo

### 3. JSON dovrebbe essere una serializzazione ufficiale orientata alle macchine

JSON e' ottimo per:

- parser rigorosi
- interscambio tool-to-tool
- implementazioni embedded
- pipeline automatiche

### 4. JSON Schema dovrebbe essere usato per la validazione strutturale

Questo permette di vincolare in modo rigoroso la forma dei documenti,
anche quando la serializzazione scelta e' YAML.

### 5. L'estensione del file puo' restare convenzionale

Possibili convenzioni:

- `openvdl.yaml`
- `openvdl.json`
- eventualmente `.ovdl` come estensione di ecosistema

## Suggerimento finale

La posizione architetturalmente piu' forte per OpenVDL e' questa:

- non legare lo standard a YAML
- usare YAML come sintassi comoda
- mantenere il modello indipendente dal formato

In pratica:

- **YAML per gli umani**
- **JSON per le macchine**
- **JSON Schema per la validazione della struttura**

Questa scelta rende OpenVDL piu' robusto come standard, piu'
interoperabile tra implementazioni, e meno esposto ai limiti specifici
di un singolo formato di serializzazione.
