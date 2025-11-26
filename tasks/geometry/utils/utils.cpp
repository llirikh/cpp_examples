#include "utils.hpp"

bool utils::is_equal(double first, double second) {
    return std::fabs(first - second) < kEps;
}

long long utils::quantize(double value) {
    return static_cast<long long>(std::floor(value));
}