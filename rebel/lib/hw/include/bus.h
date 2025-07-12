//
// Created by pouyan on 1/13/25.
//

#ifndef BUS_H
#define BUS_H

#include <Embedded_Template_Library.h>
#include <etl/vector.h>

namespace Rebel {
  class Bus {
    public:
      virtual ~Bus() = default;

      /**
       * @brief Send message on bus
       */
      virtual void Publish(etl::ivector<int, 20> msg) = 0;
  };
}

#endif //BUS_H
