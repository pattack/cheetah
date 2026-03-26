//
// Created by pouyan on 3/15/26.
//

#include <cstring>

#include <rebel/habilis/device/usart.hpp>

namespace Rebel::Habilis::Device {
    USART::USART(USART_TypeDef *instance, uint32_t baudrate) : huart{} {
        this->configure(instance, baudrate);
    }

    bool USART::write(const char *message) {
        while (HAL_UART_GetState(&this->huart) != HAL_UART_STATE_READY) {
        }

        return HAL_UART_Transmit(&this->huart, reinterpret_cast<uint8_t *>(const_cast<char *>(message)),
                                 std::strlen(message), 100) == HAL_OK;
    }

    void USART::configure(USART_TypeDef *instance, uint32_t baudrate) {
        this->huart.Instance = instance;
        this->huart.Init.BaudRate = baudrate;
        this->huart.Init.WordLength = UART_WORDLENGTH_8B;
        this->huart.Init.StopBits = UART_STOPBITS_1;
        this->huart.Init.Parity = UART_PARITY_NONE;
        this->huart.Init.Mode = UART_MODE_TX_RX;
        this->huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        this->huart.Init.OverSampling = UART_OVERSAMPLING_16;
        if (HAL_UART_Init(&this->huart) != HAL_OK) {
            // todo: log error
        }
    }
};
