#ifndef UTILITY_HPP
#include <type_traits>
#include <random>

namespace Utility
{
    template <typename T>
    T random(T min, T max)
    {
        static std::mt19937 gen(std::random_device{}());

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(gen);
        }
        else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(gen);
        }
        else {
            static_assert(std::is_arithmetic_v<T>, "type must be integral or floating point");
        }
    }
};

#define UTILITY_HPP
#endif // UTILITY_HPP