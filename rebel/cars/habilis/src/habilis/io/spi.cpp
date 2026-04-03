//
// Created by pouyan on 3/15/26.
//

#include <habilis/io/spi.hpp>

namespace Habilis {
    SPI::SPI(SPI_TypeDef *instance) : hspi() {
        this->configure(instance);
    }

    void SPI::configure(SPI_TypeDef *instance) {
        this->hspi.Instance = instance;
        this->hspi.Init.Mode = SPI_MODE_MASTER;
        this->hspi.Init.Direction = SPI_DIRECTION_2LINES;
        this->hspi.Init.DataSize = SPI_DATASIZE_8BIT;
        this->hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
        this->hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
        this->hspi.Init.NSS = SPI_NSS_SOFT;
        this->hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
        this->hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
        if (HAL_SPI_Init(&this->hspi) != HAL_OK) {
            // todo: indicate failure
        }
    }
};
