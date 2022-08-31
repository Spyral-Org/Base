#include "Hash.hpp"

namespace Spyral
{
    /**
     * @brief Generate a 32bit hash from a string
     */
    constexpr hash Hash(const std::string_view b)
    {
        hash result = 0;

        for (auto c : b)
        {            
            result += c & 0x0FFL; // to lower, I'm assuming?
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
    constexpr long_hash LongHash(const std::string_view b)
    {
        long_hash result = 0;

        for (auto c : b)
        {            
            result += c & 0x0FFL;
            result += (result << 20);
            result ^= (result >> 12);
        }
        
        result += (result << 6);
        result ^= (result >> 22);
        result += (result << 30);

        return result;
    }

    constexpr hash operator ""_H(const char* s, std::size_t n)
    {
        return Hash(std::string(s, n));
    }

    constexpr long_hash operator ""_LH(const char* s, std::size_t n)
    {
        return LongHash(std::string(s, n));
    }
}