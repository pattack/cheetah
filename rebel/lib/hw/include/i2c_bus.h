//
// Created by pouyan on 1/13/25.
//

#ifndef IWC_BUS_H
#define IWC_BUS_H

#include <vector>

namespace Rebel {
  class I2CBus {
    public:
      I2CBus();

      void Publish(std::vector<int> msg) override;
  };
}

#endif //IWC_BUS_H
