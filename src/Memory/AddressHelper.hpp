#pragma once
#include <cstdint>

namespace Spyral
{
    class AddressHelper
    {
    private:
        AddressHelper(const std::uintptr_t addr);

    public:
        AddressHelper(void* addr);
        virtual ~AddressHelper() = default;

        /**
         * @brief Add to the current address
         * 
         * @return AddressHelper 
         */
        AddressHelper Add(const std::uintptr_t offset);
        /**
         * @brief Subtract from the current address
         * 
         * @return AddressHelper 
         */
        AddressHelper Sub(const std::uintptr_t offset);
        /**
         * @brief Reads the value at the current address and sets returns an AddressHelper from that address.
         * 
         * @return AddressHelper 
         */
        AddressHelper Absolute();
        /**
         * @brief Follow the relative offset at the current address rip/lea/jmp/...
         * 
         * @return AddressHelper 
         */
        AddressHelper Relative();

        /**
         * Cast the current address to a specific type.
         */
        template<typename T>
        T As();

    private:
        std::uintptr_t m_Addr;

    };

    template<typename T>
    inline T AddressHelper::As()
    {
        return reinterpret_cast<T>(m_Addr);
    }
}