#pragma once
#include <cstdint>
#include <string_view>

namespace Spyral
{
    using joaat_t = uint32_t;
    using long_joaat_t = uint64_t;

    /**
     * @brief Generate a 32bit hash from a string
     */
    extern constexpr joaat_t Joaat(const std::string_view b);
    /**
     * @brief Generate a 64bit hash from a string
     */
    extern constexpr long_joaat_t LongJoaat(const std::string_view b);

    extern constexpr joaat_t operator ""_J(const char* s, std::size_t n);
    extern constexpr long_joaat_t operator ""_LJ(const char* s, std::size_t n);
}