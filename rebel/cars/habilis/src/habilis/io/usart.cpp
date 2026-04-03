//
// Created by pouyan on 3/15/26.
//

#include <string>

#include <habilis/io/usart.hpp>

namespace Habilis {
    USART::USART(USART_TypeDef *instance, const uint32_t baudRate) : husart{} {
        this->configure(instance, baudRate);
    }

    bool USART::write(std::string_view message) {
        this->wait_for_readiness();

        return HAL_USART_Transmit_IT(&this->husart, reinterpret_cast<uint8_t *>(const_cast<char *>(message.data())),
                                     message.length()) == HAL_OK;
    }

    const std::string &USART::read() {
        std::string buffer{};

        const auto rx = new uint8_t();
        for (;;) {
            this->wait_for_readiness();

            if (const auto status = HAL_USART_Receive_IT(&this->husart, rx, 1); status == HAL_OK) {
                if (*rx == '\n') {
                    break;
                }

                buffer += *rx;
            } else {
                break;
            }
        }

        return std::move(buffer);
    }

    void USART::handle_irq() {
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

    void USART::wait_for_readiness() {
        while (HAL_USART_GetState(&this->husart) != HAL_USART_STATE_READY) {
        }
    }
};
