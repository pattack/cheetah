//
// Created by pouyan on 3/15/26.
//

#include <cstring>

#include <rebel/habilis/device/usart.hpp>

namespace Rebel::Habilis::Device {
    USART::USART(USART_TypeDef *instance, const uint32_t baudRate) : husart{} {
        this->configure(instance, baudRate);
    }

    bool USART::write(const char *message) {
        while (HAL_USART_GetState(&this->husart) != HAL_USART_STATE_READY) {
        }

        return HAL_USART_Transmit_IT(&this->husart, reinterpret_cast<uint8_t *>(const_cast<char *>(message)),
                                 std::strlen(message)) == HAL_OK;
    }

    void USART::handleIRQ() {
        HAL_USART_IRQHandler(&this->husart);
    }

    void USART::configure(USART_TypeDef *instance, const uint32_t baudRate) {
        this->husart.Instance = instance;
        this->husart.Init.BaudRate = baudRate;
        this->husart.Init.WordLength = USART_WORDLENGTH_8B;
        this->husart.Init.StopBits = USART_STOPBITS_1;
        this->husart.Init.Parity = USART_PARITY_NONE;
        this->husart.Init.Mode = USART_MODE_TX_RX;
        if (HAL_USART_Init(&this->husart) != HAL_OK) {
            // todo: indicate failure
        }
    }
};
