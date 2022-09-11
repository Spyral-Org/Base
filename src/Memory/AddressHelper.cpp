#include "AddressHelper.hpp"

namespace Spyral
{
    AddressHelper::AddressHelper(const std::uintptr_t addr)
        : m_Addr(addr)
    {

    }

    AddressHelper::AddressHelper(void* addr)
    {
        m_Addr = reinterpret_cast<std::uintptr_t>(addr);
    }

    AddressHelper AddressHelper::Add(const std::uintptr_t offset)
    {
        return m_Addr + offset;
    }

    AddressHelper AddressHelper::Sub(const std::uintptr_t offset)
    {
        return m_Addr - offset;
    }

    AddressHelper AddressHelper::Absolute()
    {
        return *As<void**>();
    }

    AddressHelper AddressHelper::Relative()
    {
        return m_Addr + *As<std::int32_t*>() + 4;
    }
}