# AGENTS Guidelines (Rebel)

This document defines project context and code-of-conduct rules for AI agents working on Rebel.

## Project Context

- `Cheetah` is a smart remotely-controlled car platform.
- `Rebel` is a Cheetah subproject containing car hardware and software.

## Architecture Boundaries

- `cars/`: board-specific hardware/software implementations (BSP-like OS layer).
- `apps/`: hardware-agnostic applications that implement car behavior and application logic.
- `lib/`: protocol and contract layer between car and apps, defined via interfaces.

## Habilis Hardware Profile

- MCU: `STM32F401CE`.
- Shared I2C bus: `I2C1`
  - `PB6` = `SCL`
  - `PB7` = `SDA`
- I2C pull-ups:
  - `4.7k` on `SCL`
  - `4.7k` on `SDA`

### I2C1 Devices

- `PCA9685` at `0x41`
- `ADS1110` at `0x48`
- `24C04A` at `0x50`
- Proteus I2C debugger

## Other Peripherals

- Virtual Terminal on `USART1`
  - `PA9` = `TX`
  - `PA10` = `RX`
- `L298` is connected to `LED0` and `LED1` outputs of `PCA9685`.

## AI Agent Code Of Conduct

- Preserve architecture boundaries:
  - Do not place board-specific logic in `apps/`.
  - Do not place app/business logic in `cars/`.
  - Keep cross-layer contracts in `lib/`.
- Treat hardware facts in this file as source-of-truth unless the user explicitly updates them.
- Keep pin mappings, addresses, and bus assignments explicit in code and docs.
- Prefer minimal, auditable changes over broad refactors.
- Maintain backward compatibility of interfaces unless a breaking change is explicitly requested.
- For hardware-facing changes, include safety-oriented defaults and failure handling (timeouts, invalid data checks, and safe stop behavior when applicable).
- If assumptions are required, state them clearly in commit/PR notes or task summary.

## Structural And Contribution Lessons

- Keep simulator-facing artifacts board-local:
  - Board-specific simulation behavior must live under `cars/<board>/...` and be referenced from `cars/<board>/board.resc`.
  - Keep `cars/emulation.resc.tpl` generic and reusable across boards.
- Prefer narrow, explicit contracts between firmware and simulation:
  - If simulation setup needs parameters, pass them explicitly from `board.resc` instead of relying on implicit globals.
- Minimize long-lived debug patches in firmware:
  - Temporary simulation workarounds (timeouts, retries, probes) should be clearly marked and removed once root cause is known.
- Keep instrumentation clean:
  - Prefer targeted, bounded logs with clear status/error fields over broad verbose prints.

## Architectural Decision Notes (ADR-lite)

- Decision: Use Renode custom behavior scripts for unsupported peripherals (`ADS1110`, `PCA9685`, `24C04A`).
  - Rationale: No known upstream Renode models for these exact devices.
  - Consequence: Maintain a small in-repo behavior model and validate against Proteus/hardware behavior.
- Decision: Use Proteus and hardware behavior as functional reference for I2C transaction shape.
  - Rationale: Current fidelity for these peripherals is higher in Proteus than in generic Renode mocks.
  - Consequence: Renode remains useful for deterministic CI flows, but protocol correctness must be cross-checked.

## I2C Design And Debug Lessons (ADS1110 Read Path)

- Address ACK alone does not prove a valid read transaction; always verify data phase completion.
- For ADS1110 reads, treat the expected frame shape explicitly:
  - Typical read transaction is `S + 0x91 + A + <data bytes> + ... + P`.
- When bus lines get stuck (`SDA` or `SCL` held low), debug in this order:
  1. Confirm pin mode/AF configuration for `PB6/PB7` and pull-ups.
  2. Confirm no conflicting peripheral/device drives the same lines.
  3. Isolate device interactions: test ADS1110 read in a minimal loop with other I2C traffic disabled.
  4. Log both HAL return status and `HAL_I2C_GetError()` on every failed transaction.
  5. Perform explicit bus recovery before re-init if BUSY/stuck is detected (clock out SCL pulses and generate STOP where applicable).
- Avoid relying on side-effect probes (e.g., random address checks) as a permanent fix; if a probe “unblocks” bus behavior, treat it as a symptom and root-cause the init/transaction ordering.
