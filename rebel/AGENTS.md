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
