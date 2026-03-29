//
// Created by pouyan on 3/29/26.
//

#pragma once

#include <rebel/habilis/component/led.hpp>

namespace Rebel::Habilis::Module {
    class Indicator {
    public:
        explicit Indicator(const Rebel::Habilis::Component::LED &ledStatus, const Rebel::Habilis::Component::LED &ledError);

        void showTransient() const;
        void showSteady() const;
        void showError() const;

    private:
        Rebel::Habilis::Component::LED ledStatus;
        Rebel::Habilis::Component::LED ledError;
    };
};
