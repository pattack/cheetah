//
// Created by pouyan on 3/31/26.
//

#pragma once

namespace Rebel {
    template<typename T>
    class Writer {
    public:
        virtual ~Writer() = default;

        virtual void write(T data) = 0;
    };
}
