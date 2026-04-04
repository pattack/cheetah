//
// Created by pouyan on 4/1/26.
//

#pragma once

#include <string>

#include <rebel/io/reader.hpp>

namespace Rebel {
    class Scanner : public Reader<const std::string &> {
    };
}
