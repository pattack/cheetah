//
// Created by pouyan on 7/23/25.
//

#include <cstring>

#include <rebel/habilis/toolkit/usart_logger.hpp>

UART_HandleTypeDef newUart(USART_TypeDef* Instance);
void printOnUart(UART_HandleTypeDef* huart, const char* message);

namespace Rebel::Habilis::Toolkit
{
    UsartLogger::UsartLogger(USART_TypeDef* Instance)
    {
        this->initHuart(Instance);
    }

    void UsartLogger::initHuart(USART_TypeDef* Instance)
    {
        this->huart.Instance = Instance;
        this->huart.Init.BaudRate = 9600;
        this->huart.Init.WordLength = UART_WORDLENGTH_8B;
        this->huart.Init.StopBits = UART_STOPBITS_1;
        this->huart.Init.Parity = UART_PARITY_NONE;
        this->huart.Init.Mode = UART_MODE_TX_RX;
        this->huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        this->huart.Init.OverSampling = UART_OVERSAMPLING_16;

        HAL_UART_Init(&this->huart);
    }

    void UsartLogger::Log(const char* message)
    {
        HAL_UART_Transmit(&this->huart, reinterpret_cast<uint8_t*>(const_cast<char*>(message)),
                          std::strlen(message), HAL_MAX_DELAY);
    }
}
