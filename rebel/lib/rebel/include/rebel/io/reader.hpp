//
// Created by pouyan on 3/31/26.
//

#pragma once

namespace Rebel {
    template<typename T>
    class Reader {
    public:
        virtual ~Reader() = default;

        virtual T read() = 0;
    };
}
