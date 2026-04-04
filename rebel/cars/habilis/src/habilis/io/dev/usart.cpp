//
// Created by pouyan on 3/15/26.
//

#include <string>

#include <habilis/io/dev/usart.hpp>

namespace Habilis {
    USART::USART(USART_TypeDef *instance, const uint32_t baudRate) {
        this->configure(instance, baudRate);
    }

    bool USART::write(std::string_view message) const {
        this->wait_for_readiness();

        return HAL_USART_Transmit(this->m_husart.get(), reinterpret_cast<uint8_t *>(const_cast<char *>(message.data())),
                                     message.length(), 100) == HAL_OK;
    }

    const std::string &USART::read() const {
        std::string buffer{};

        const auto rx = new uint8_t();
        for (;;) {
            this->wait_for_readiness();

            if (const auto status = HAL_USART_Receive(this->m_husart.get(), rx, 1, 100); status == HAL_OK) {
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

    void USART::handle_irq() const {
        HAL_USART_IRQHandler(this->m_husart.get());
    }

    void USART::configure(USART_TypeDef *instance, const uint32_t baudRate) {
        this->m_husart = std::make_shared<USART_HandleTypeDef>();
        this->m_husart->Instance = instance;
        this->m_husart->Init.BaudRate = baudRate;
        this->m_husart->Init.WordLength = USART_WORDLENGTH_8B;
        this->m_husart->Init.StopBits = USART_STOPBITS_1;
        this->m_husart->Init.Parity = USART_PARITY_NONE;
        this->m_husart->Init.Mode = USART_MODE_TX_RX;
        if (HAL_USART_Init(this->m_husart.get()) != HAL_OK) {
            // todo: indicate failure
        }
    }

    void USART::wait_for_readiness() const {
        while (HAL_USART_GetState(this->m_husart.get()) != HAL_USART_STATE_READY) {
        }
    }
};
