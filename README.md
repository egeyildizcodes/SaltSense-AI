# SaltSense AI

> Adaptive Multisensory Taste Modulation System for low-sodium food perception research.

SaltSense AI is a research prototype that explores how salt perception can be influenced without increasing the actual amount of sodium in food. The project combines controlled electrical taste stimulation, thermal modulation, aroma cues, surface texture design, Bluetooth control, and adaptive user profiling into a single experimental platform.

This repository documents the concept, hardware architecture, firmware, safety limits, research background, experimental design, and future mobile-app roadmap.

---

## Core Idea

Most low-sodium foods fail because people do not only need less sodium; they need the *perception* of saltiness, flavor intensity, mouthfeel, and satisfaction. SaltSense AI treats saltiness as a multisensory perception problem instead of a simple chemical-additive problem.

The system is based on this central hypothesis:

> A low-sodium food can be perceived as saltier when electrical stimulation, temperature, aroma, surface texture, and personal calibration are combined into an adaptive taste interface.

---

## What Makes This Different

This is not only an electric salt spoon. The intended final system is a complete taste-modulation platform:

- Electrical taste modulation using a DAC-generated waveform
- Smooth cathodal/anodal waveform phases instead of raw DC output
- Temperature-aware taste enhancement through a controlled heating module
- Aroma-assisted saltiness/umami perception using replaceable aroma cartridges
- Texture-based mouthfeel modulation through interchangeable spoon tips
- Bluetooth-controlled ESP32 firmware
- User calibration for sensitivity, comfort, and metallic-taste threshold
- Future wearable-health-data integration for adaptive taste profiles
- Safety-first research workflow with non-human dummy-load validation

---

## System Architecture

```text
Wearable / mobile data
        ↓
Mobile app / AI profile engine
        ↓
Bluetooth command layer
        ↓
ESP32 controller
        ↓
DAC waveform generator
        ↓
Analog buffer + current limiting
        ↓
Spoon electrode / experimental output

Additional sensory layers:
- Thermal module
- Aroma cartridge
- Texture tip
- RGB / haptic feedback
```

---

## Planned Hardware Stack

| Block | Component |
|---|---|
| Controller | ESP32 DevKit V1 / ESP32-WROOM-32 |
| DAC | MCP4725 12-bit I2C DAC |
| Analog buffer | MCP6002 or similar low-voltage op-amp |
| Output protection | High-value series resistor, test/sense points |
| Heating | 5V mini heater pad + MOSFET |
| Temperature | DS18B20 or NTC thermistor |
| Aroma | Small cartridge + optional 5V micro fan |
| Feedback | RGB LED + vibration motor |
| Power | Battery powered only during isolated tests |
| PCB target | 80 mm x 45 mm, 2-layer prototype board |

---

## Repository Structure

```text
SaltSense-AI/
├── README.md
├── LICENSE
├── .gitignore
├── firmware/
│   ├── esp32/
│   │   ├── main.ino
│   │   └── README.md
│   └── waveform_reference/
│       └── waveform_model.py
├── hardware/
│   ├── bom.csv
│   ├── pinout.md
│   ├── pcb_spec.md
│   ├── schematic_connections.md
│   └── mechanical_design.md
├── docs/
│   ├── architecture.md
│   ├── theory.md
│   ├── safety.md
│   ├── experiments.md
│   ├── firmware.md
│   ├── mobile_app_concept.md
│   ├── roadmap.md
│   └── project_pitch.md
├── research/
│   ├── literature_map.md
│   ├── research_notes.md
│   └── experiment_protocol.md
└── app/
    └── mobile-app/
        └── README.md
```

---

## Current Status

This repository is in the concept/prototype documentation phase. The firmware includes a safe-by-default ESP32 control skeleton for waveform generation and module control. Hardware documentation is written as a design target, not a certified medical or consumer design.

---

## Safety Notice

SaltSense AI is a research prototype. It is **not** a medical device, not a consumer product, and not intended for unsupervised human use. Any electrical output intended for taste research must be validated with external measurement equipment and non-human dummy loads before any further evaluation.

Do not connect this system to mains-powered supplies, wall adapters, laptop USB power, bench supplies, or powerbanks during any contact-related experiment. Human testing requires adult supervision, ethics review where applicable, proper isolation, current limiting, emergency stop behavior, and documented informed consent.

See [`docs/safety.md`](docs/safety.md) before building or testing anything.

---

## Project Vision

SaltSense AI aims to become an adaptive nutrition-technology interface that helps investigate whether low-sodium foods can feel more satisfying through perception engineering rather than chemical sodium increase.

The final vision combines:

- Taste neuroscience
- Embedded electronics
- Wearable health data
- Human-computer interaction
- Sensory design
- Food technology
- AI-driven personalization

---

## License

MIT License. See [`LICENSE`](LICENSE).
