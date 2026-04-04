//
// Created by pouyan on 3/29/26.
//

#pragma once

#include <habilis/io/com/led.hpp>

namespace Habilis {
    class Indicator {
    public:
        explicit Indicator(LED ledStatus, LED ledError);

        void showTransient() const;
        void showSteady() const;
        void showError() const;

    private:
        LED ledStatus;
        LED ledError;
    };
};
