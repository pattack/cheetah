//
// Created by pouyan on 3/29/26.
//

#include <habilis/kit.hpp>

#include <habilis/hal/i2c.h>

/**
  * @brief I2C MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c) {
    GPIO_InitTypeDef igpio {};
    igpio.Mode = GPIO_MODE_AF_OD;
    igpio.Pull = GPIO_PULLUP;
    igpio.Speed = GPIO_SPEED_FREQ_HIGH;

    if (hi2c->Instance == I2C1) {
        /* Peripheral clock enable */
        __HAL_RCC_I2C1_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**I2C1 GPIO Configuration
        PB6     ------> I2C1_SCL
        PB7     ------> I2C1_SDA
        */
        igpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;
        igpio.Alternate = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &igpio);

        /* I2C1 interrupt Init */
        HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 1);
        HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
        HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 2);
        HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    } else if (hi2c->Instance == I2C2) {
        /* Peripheral clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**I2C2 GPIO Configuration
        PB10     ------> I2C2_SCL
        PB3     ------> I2C2_SDA
        */
        igpio.Pin = GPIO_PIN_10;
        igpio.Alternate = GPIO_AF4_I2C2;
        HAL_GPIO_Init(GPIOB, &igpio);

        igpio.Pin = GPIO_PIN_3;
        igpio.Alternate = GPIO_AF9_I2C2;
        HAL_GPIO_Init(GPIOB, &igpio);

        /* I2C2 interrupt Init */
        HAL_NVIC_SetPriority(I2C2_ER_IRQn, 0, 1);
        HAL_NVIC_EnableIRQ(I2C2_ER_IRQn);
        HAL_NVIC_SetPriority(I2C2_EV_IRQn, 0, 2);
        HAL_NVIC_EnableIRQ(I2C2_EV_IRQn);
    }
}

/**
  * @brief I2C MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        __HAL_RCC_I2C1_FORCE_RESET();
        __HAL_RCC_I2C1_RELEASE_RESET();

        /* Peripheral clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /**I2C1 GPIO Configuration
        PB6     ------> I2C1_SCL
        PB7     ------> I2C1_SDA
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

        /* I2C1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
    } else if (hi2c->Instance == I2C2) {
        __HAL_RCC_I2C2_FORCE_RESET();
        __HAL_RCC_I2C2_RELEASE_RESET();

        /* Peripheral clock disable */
        __HAL_RCC_I2C2_CLK_DISABLE();

        /**I2C2 GPIO Configuration
        PB10     ------> I2C2_SCL
        PB3     ------> I2C2_SDA
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);

        /* I2C2 interrupt DeInit */
        HAL_NVIC_DisableIRQ(I2C2_EV_IRQn);
        HAL_NVIC_DisableIRQ(I2C2_ER_IRQn);
    }
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    // I2C transmit completed
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    // I2C receive completed
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
    // I2C error
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

void I2C1_EV_IRQHandler() {
    Habilis::Kit::Default().Devices.i2c1->handleEventIRQ();
}

void I2C1_ER_IRQHandler() {
    Habilis::Kit::Default().Devices.i2c1->handleErrorIRQ();
}

void I2C2_EV_IRQHandler() {
    Habilis::Kit::Default().Devices.i2c2->handleEventIRQ();
}

void I2C2_ER_IRQHandler() {
    Habilis::Kit::Default().Devices.i2c2->handleErrorIRQ();
}