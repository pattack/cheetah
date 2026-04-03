//
// Created by pouyan on 3/29/26.
//

#include <habilis/kit.hpp>

#include <habilis/hal/usart.h>

void HAL_USART_MspInit(USART_HandleTypeDef *husart) {
    GPIO_InitTypeDef igpio {};
    igpio.Mode = GPIO_MODE_AF_PP;
    igpio.Pull = GPIO_NOPULL;
    igpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    if (husart->Instance == USART1) {
        /* Peripheral clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        igpio.Pin = GPIO_PIN_9 | GPIO_PIN_10;
        igpio.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &igpio);

        /* USART1 interrupt Init */
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    } else if (husart->Instance == USART2) {
        /* Peripheral clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        igpio.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        igpio.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &igpio);

        /* USART2 interrupt Init */
        HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    }
}

void HAL_USART_MspDeInit(USART_HandleTypeDef *husart) {
    if (husart->Instance == USART1) {
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();

        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);

        /* USART1 interrupt DeInit */
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    } else if (husart->Instance == USART2) {
        /* Peripheral clock disable */
        __HAL_RCC_USART2_CLK_DISABLE();

        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

        /* USART2 interrupt DeInit */
        HAL_NVIC_DisableIRQ(USART2_IRQn);
    }
}

void HAL_USART_TxCpltCallback(USART_HandleTypeDef *husart) {
    // USART transmit completed
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

void USART1_IRQHandler() {
    Habilis::Kit::Default().Devices.usart1->handle_irq();
}

void USART2_IRQHandler() {
    Habilis::Kit::Default().Devices.usart2->handle_irq();
}