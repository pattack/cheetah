//
// Created by pouyan on 7/25/25.
//

#include <rebel/habilis/hal/hal.h>

#include <rebel/habilis/kit.hpp>

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/

extern "C" {
    [[noreturn]] void NMI_Handler();
    [[noreturn]] void HardFault_Handler();
    [[noreturn]] void MemManage_Handler();
    [[noreturn]] void BusFault_Handler();
    [[noreturn]] void UsageFault_Handler();
    void SVC_Handler();
    void DebugMon_Handler();
    void PendSV_Handler();
    void SysTick_Handler();
}

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler() {
    while (true);
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler() {
    while (true);
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler() {
    while (true);
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler() {
    while (true);
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler() {
    while (true);
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler() {
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler() {
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler() {
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler() {
    HAL_IncTick();
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

extern "C" {
    void USART1_IRQHandler();
    void USART2_IRQHandler();
    void I2C1_EV_IRQHandler();
    void I2C1_ER_IRQHandler();
    void I2C2_EV_IRQHandler();
    void I2C2_ER_IRQHandler();
}

void USART1_IRQHandler() {
    Rebel::Habilis::Kit::Default().Devices.usart1->handleIRQ();
}

void USART2_IRQHandler() {
    Rebel::Habilis::Kit::Default().Devices.usart2->handleIRQ();
}

void I2C1_EV_IRQHandler() {
    Rebel::Habilis::Kit::Default().Devices.i2c1->handleEventIRQ();
}

void I2C1_ER_IRQHandler() {
    Rebel::Habilis::Kit::Default().Devices.i2c1->handleErrorIRQ();
}

void I2C2_EV_IRQHandler() {
    Rebel::Habilis::Kit::Default().Devices.i2c2->handleEventIRQ();
}

void I2C2_ER_IRQHandler() {
    Rebel::Habilis::Kit::Default().Devices.i2c2->handleErrorIRQ();
}
