# AGENTS Guidelines (Rebel)

This document defines high-level context and engineering principles for AI agents working on Rebel.

## Project Context

- `Cheetah` is a smart remotely-controlled car platform.
- `Rebel` is a Cheetah subproject containing car hardware and software.

## Architecture Boundaries

- `cars/`: board-specific BSP-like hardware/software layer.
- `apps/`: hardware-agnostic application logic.
- `lib/`: cross-layer contracts and communication interfaces.

Keep these boundaries strict:
- No board-specific logic in `apps/`.
- No app/business logic in `cars/`.
- Shared contracts must live in `lib/`.

## Habilis Hardware Source Of Truth

- MCU: `STM32F401CE`.
- Shared I2C bus: `I2C1` (`PB6=SCL`, `PB7=SDA`) with `4.7k` pull-ups on both lines.
- I2C1 devices:
  - `PCA9685 @ 0x41`
  - `ADS1110 @ 0x48`
  - `TC74 @ 0x4D`
  - `24C04A @ 0x50`
  - Proteus I2C debugger
- Virtual terminal: `USART1` (`PA9=TX`, `PA10=RX`).
- `L298` is connected to `LED0` and `LED1` outputs of `PCA9685`.

Treat this hardware profile as authoritative unless explicitly updated by the user.

## Engineering Principles

- Prefer root-cause fixes over symptom suppression.
- Avoid ad-hoc hacks that depend on fragile simulator/toolchain side effects.
- Keep changes minimal, auditable, and reversible.
- Preserve interface compatibility unless a breaking change is explicitly requested.
- Make build and runtime behavior deterministic across environments.
- Keep board-specific simulation details local to board files; keep shared templates generic.
- State assumptions and tradeoffs clearly in task summaries.

## Build And Compatibility Policy

- Favor explicit, stable build contracts over implicit compiler defaults.
- Pin language semantics intentionally (via explicit standard settings), while allowing toolchain upgrades.
- Do not rely on undefined behavior, toolchain quirks, or parser-specific artifacts.
- When simulator behavior diverges from hardware expectations, validate against hardware datasheets and protocol-level evidence first.
