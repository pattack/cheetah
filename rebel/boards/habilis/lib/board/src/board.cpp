//
// Created by pouyan on 7/15/25.
//

#include <cstddef>

#include <stm32f1xx_hal.h>

#include <rebel/board/board.hpp>

UART_HandleTypeDef huart1;

void configureUart1()
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 9600;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&huart1);
}

void uartPrint(const char* msg)
{
    HAL_UART_Transmit(&huart1, reinterpret_cast<uint8_t*>(const_cast<char*>(msg)), 18, HAL_MAX_DELAY);
}

namespace Rebel::Board
{
    void Board::Configure()
    {
        configureUart1();
        uartPrint("Hello from Habilis\r\n");
    }
}
