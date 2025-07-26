//
// Created by pouyan on 7/23/25.
//

#include <cstring>

#include <rebel/habilis/toolkit/usart_logger.hpp>

namespace Rebel::Habilis::Toolkit
{
    UsartLogger::UsartLogger(USART_TypeDef* instance, uint32_t baudrate)
    {
        this->configure(instance, baudrate);
    }

    void UsartLogger::Log(const char* message)
    {
        HAL_UART_Transmit(&this->huart, reinterpret_cast<uint8_t*>(const_cast<char*>(message)),
                          std::strlen(message), HAL_MAX_DELAY);
    }

    void UsartLogger::configure(USART_TypeDef* instance, uint32_t baudrate)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();

        GPIO_InitTypeDef igpio = {};
        igpio.Pin = GPIO_PIN_9;
        igpio.Mode = GPIO_MODE_AF_PP;
        igpio.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &igpio);

        this->huart.Instance = instance;
        this->huart.Init.BaudRate = baudrate;
        this->huart.Init.WordLength = UART_WORDLENGTH_8B;
        this->huart.Init.StopBits = UART_STOPBITS_1;
        this->huart.Init.Parity = UART_PARITY_NONE;
        this->huart.Init.Mode = UART_MODE_TX_RX;
        this->huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        this->huart.Init.OverSampling = UART_OVERSAMPLING_16;
        HAL_UART_Init(&this->huart);
    }
}
