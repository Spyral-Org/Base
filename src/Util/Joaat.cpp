#include "Joaat.hpp"

namespace Spyral
{
    constexpr char ToLower(char c)
    {
        return c >= 'A' && c <= 'Z' ? c | 1 << 5 : c;
    }

    /**
     * @brief Generate a 32bit hash from a string
     */
    constexpr joaat_t Joaat(const std::string_view b)
    {
        joaat_t result = 0;

        for (auto c : b)
        {            
            result += ToLower(c);
            result += (result << 10);
            result ^= (result >> 6);
        }
        
        result += (result << 3);
        result ^= (result >> 11);
        result += (result << 15);

        return result;
    }

    /**
     * @brief Generate a 64bit hash from a string
     */
    constexpr long_joaat_t LongJoaat(const std::string_view b)
    {
        long_joaat_t result = 0;

        for (auto c : b)
        {            
            result += ToLower(c);
            result += (result << 20);
            result ^= (result >> 12);
        }
        
        result += (result << 6);
        result ^= (result >> 22);
        result += (result << 30);

        return result;
    }

    constexpr joaat_t operator ""_J(const char* s, std::size_t n)
    {
        return Joaat(std::string(s, n));
    }

    constexpr long_joaat_t operator ""_LJ(const char* s, std::size_t n)
    {
        return LongJoaat(std::string(s, n));
    }
}