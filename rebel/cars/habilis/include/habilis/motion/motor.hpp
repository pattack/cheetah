//
// Created by pouyan on 3/31/26.
//

#pragma once

namespace Habilis {
    class Motor {
    public:
        virtual ~Motor() = default;

        virtual void revolve(float rate, bool cw) = 0;

        virtual int rpm() = 0;
    };
}
