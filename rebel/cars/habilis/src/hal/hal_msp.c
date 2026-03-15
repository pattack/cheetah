/**
  ******************************************************************************
  * @file         hal_msp.c
  * @author       Pouyan Heyratpour
  * @brief        This file provides code for the MSP Initialization
  *               and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include <rebel/habilis/hal/hal.h>

/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    /* System interrupt init*/
    // HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(USART1_IRQn);

    // HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

    // HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
    // HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
}

/**
  * @brief I2C MSP Initialization
  * This function configures the hardware resources used in this example
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
    GPIO_InitTypeDef igpio = {0};
    igpio.Mode = GPIO_MODE_AF_OD;
    igpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    igpio.Pull = GPIO_PULLUP;

    if (hi2c->Instance == I2C1)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**I2C1 GPIO Configuration
        PB6     ------> I2C1_SCL
        PB7     ------> I2C1_SDA
        */
        igpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;
        igpio.Alternate = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB, &igpio);

        /* Peripheral clock enable */
        __HAL_RCC_I2C1_CLK_ENABLE();
    }
    else if (hi2c->Instance == I2C2)
    {
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

        /* Peripheral clock enable */
        __HAL_RCC_I2C2_CLK_ENABLE();
    }
}

/**
  * @brief I2C MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param hi2c: I2C handle pointer
  * @retval None
  */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();

        /**I2C1 GPIO Configuration
        PB6     ------> I2C1_SCL
        PB7     ------> I2C1_SDA
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);
    }
    else if (hi2c->Instance == I2C2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_I2C2_CLK_DISABLE();

        /**I2C2 GPIO Configuration
        PB10     ------> I2C2_SCL
        PB3     ------> I2C2_SDA
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);
    }
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef* hi2c)
{

}

/**
  * @brief UART MSP Initialization
  * This function configures the hardware resources used in this example
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef igpio = {0};
    if (huart->Instance == USART1)
    {
        /* Peripheral clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        igpio.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        igpio.Mode = GPIO_MODE_AF_PP;
        igpio.Pull = GPIO_NOPULL;
        igpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        igpio.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &igpio);

        /* USART1 interrupt Init */
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    else if (huart->Instance == USART2)
    {
        /* Peripheral clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        igpio.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        igpio.Mode = GPIO_MODE_AF_PP;
        igpio.Pull = GPIO_NOPULL;
        igpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        igpio.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &igpio);
    }
}

/**
  * @brief UART MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
    if (huart->Instance == USART1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();

        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

        /* USART1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
    else if (huart->Instance == USART2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART2_CLK_DISABLE();

        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

}

void HAL_USART_MspInit(USART_HandleTypeDef* husart)
{
    GPIO_InitTypeDef igpio = {0};
    if (husart->Instance == USART1)
    {
        /* Peripheral clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        igpio.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        igpio.Mode = GPIO_MODE_AF_PP;
        igpio.Pull = GPIO_NOPULL;
        igpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        igpio.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &igpio);

        /* USART1 interrupt Init */
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    else if (husart->Instance == USART2)
    {
        /* Peripheral clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        igpio.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        igpio.Mode = GPIO_MODE_AF_PP;
        igpio.Pull = GPIO_NOPULL;
        igpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        igpio.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &igpio);
    }
}

void HAL_USART_MspDeInit(USART_HandleTypeDef* husart)
{
    if (husart->Instance == USART1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();

        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

        /* USART1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
    else if (husart->Instance == USART2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART2_CLK_DISABLE();

        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
    }
}

void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart)
{

}

Peripherals *connectedDevices;

void SetPeripherals(Peripherals *peripherals)
{
    connectedDevices = peripherals;
}

Peripherals* GetPeripherals()
{
    return connectedDevices;
}
