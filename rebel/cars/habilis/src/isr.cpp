//
// Created by pouyan on 7/25/25.
//

#include <stm32f1xx_hal.h>

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
extern "C" void SysTick_Handler(void)
{
    HAL_IncTick();
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
extern "C" void HardFault_Handler(void)
{
}

/**
  * Brief   This function handles I2C1 (Slave) event interrupt request.
  * Param   None
  * Retval  None
  */
extern "C" void I2C1_EV_IRQHandler(void)
{
    // todo: HAL_I2C_EV_IRQHandler(&hi2c);
}

/**
  * Brief   This function handles I2C1 (Master) error interrupt request.
  * Param   None
  * Retval  None
  */
extern "C" void I2C1_ER_IRQHandler(void)
{
    // todo: HAL_I2C_ER_IRQHandler(&hi2c);
}
