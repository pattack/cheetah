//
// Created by pouyan on 3/15/26.
//

#pragma once

#include <rebel/habilis/hal/hal.h>

namespace Rebel::Habilis::Device {
    class SPI {
    public:
        explicit SPI(SPI_TypeDef *instance);

    private:
        SPI_HandleTypeDef hspi;

    protected:
        void configure(SPI_TypeDef *instance);
    };
};