#pragma once
#include "../common.hpp"

namespace Spyral
{
    constexpr uint64_t operator ""_fnv1a(char const *str, std::size_t len)
    {
        auto const fnv_offset_basis = 14695981039346656037ULL;
        auto const fnv_prime = 1099511628211ULL;

        auto value = fnv_offset_basis;
        for (auto i = 0; i < len; i++) {
            value ^= static_cast<size_t>(str[i]);
            value *= fnv_prime;
        }
        value ^= value >> 32;

        return value;
    }
}