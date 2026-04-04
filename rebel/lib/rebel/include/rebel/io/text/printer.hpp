//
// Created by pouyan on 4/1/26.
//

#pragma once

#include <string_view>

#include <rebel/io/writer.hpp>

namespace Rebel {
    class Printer : public Writer<std::string_view> {
    };
}
