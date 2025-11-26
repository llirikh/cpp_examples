#pragma once
#include <cmath>

namespace utils {
    inline constexpr double kEps = 1e-7;

    bool is_equal(double first, double second);

    long long quantize(double value);
}