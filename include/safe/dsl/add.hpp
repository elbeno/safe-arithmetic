#pragma once

#include <safe/dsl/ival.hpp>
#include <safe/dsl/mask.hpp>
#include <safe/dsl/primitive.hpp>
#include <safe/dsl/fwd.hpp>

namespace safe::dsl {
    template<typename T, typename U>
    struct add : public detail::binary_op {};

    template<
        Interval LhsT,
        Interval RhsT>
    struct add<LhsT, RhsT>
        : public detail::binary_op
    {
        using type = ival_t<
            LhsT::min + RhsT::min,
            LhsT::max + RhsT::max
        >;
    };

    template<
        Mask LhsT,
        Mask RhsT>
    struct add<LhsT, RhsT>
        : public detail::binary_op
    {
        constexpr static auto value = LhsT::value + RhsT::value;
        using type = mask_t<value.var_bits(), value.const_bits()>;
    };


    template<
        Operand LhsT,
        Operand RhsT>
    [[nodiscard]] constexpr auto operator+(LhsT, RhsT)
        -> add<LhsT, RhsT>
    {
        return {};
    }
}