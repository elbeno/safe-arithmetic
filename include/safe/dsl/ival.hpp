#pragma once

#include <safe/detail/pure.hpp>

#include <type_traits>

namespace safe::dsl {
    template<auto Min, auto Max>
    struct ival_t {
        using type = ival_t;

        constexpr static auto min = Min;
        constexpr static auto max = Max;

        static_assert(min <= max);

        [[nodiscard]] SAFE_PURE constexpr static bool check(auto value) {
            return value >= min && value <= max;
        }
    };

    template<auto Min, auto Max>
    constexpr ival_t<Min, Max> ival{};

    template <typename T>
    constexpr bool is_ival_v = false;

    template<auto min, auto max>
    constexpr bool is_ival_v<ival_t<min, max>> = true;

    template<class T>
    concept Interval = is_ival_v<T>;
}