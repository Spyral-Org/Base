#pragma once
#include <cstdint>
#include <string_view>

namespace Spyral
{
    using hash = uint32_t;
    using long_hash = uint64_t;

    /**
     * @brief Generate a 32bit hash from a string
     */
    extern constexpr hash Hash(const std::string_view b);
    /**
     * @brief Generate a 64bit hash from a string
     */
    extern constexpr long_hash LongHash(const std::string_view b);

    extern constexpr hash operator ""_H(const char* s, std::size_t n);
    extern constexpr long_hash operator ""_LH(const char* s, std::size_t n);
}