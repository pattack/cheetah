//
// Created by pouyan on 7/21/25.
//

#pragma once

namespace Rebellion {
    class Application {
    public:
        void Run();

    private:
        void OnThrottle(float pressure);

        void OnSteer(float angle);

        void OnBrake(float pressure);
    };
}
