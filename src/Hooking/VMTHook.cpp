#include "../common.hpp"
#include "VMTHook.hpp"

namespace Spyral
{
    VMTHook::VMTHook(const std::string_view name, void*** vmtBaseAddr) :
        m_Name(name),
        m_VMTSize(VMTHook::GetVMTSize(*vmtBaseAddr)),
        m_Enabled(false),
        m_VMTBaseAddr(vmtBaseAddr)
    {
        m_OriginalVMT = *vmtBaseAddr;

        m_NewVMT = std::make_unique<void*[]>(m_VMTSize);
        memcpy(m_NewVMT.get(), m_OriginalVMT, m_VMTSize * sizeof(void*));
    }

    VMTHook::~VMTHook()
    {
        if (m_Enabled)
        {
            *m_VMTBaseAddr = m_OriginalVMT;
        }
    }

    const std::string_view VMTHook::Name() const
    {
        return m_Name;
    }

    bool VMTHook::Enable()
    {
        if (m_Enabled)
            return false;

        *m_VMTBaseAddr = m_NewVMT.get();
        m_Enabled = true;

        return true;
    }

    bool VMTHook::Disable()
    {
        if (!m_Enabled)
            return false;

        *m_VMTBaseAddr = m_OriginalVMT;
        m_Enabled = false;

        return true;
    }

    bool VMTHook::IsEnabled() const
    {
        return m_Enabled;
    }

    void VMTHook::Hook(const std::uint32_t idx, void* detour)
    {
        m_NewVMT[idx] = detour;
    }

    void VMTHook::UnHook(const std::uint32_t idx)
    {
        m_NewVMT[idx] = m_OriginalVMT[idx];
    }

    std::size_t VMTHook::VMTSize() const
    {
        return m_VMTSize;
    }

    std::size_t VMTHook::GetVMTSize(void** vmt)
    {
#ifdef _WIN64
        constexpr auto MAX_PTR_VAL = 0x000F000000000000;
#else
        constexpr auto MAX_PTR_VAL = 0xFFF00000;
#endif
        size_t i = 0;
        for (auto ptr = vmt[i]; ptr && ptr > reinterpret_cast<void*>(0x10000) && ptr < reinterpret_cast<void*>(MAX_PTR_VAL); ptr = vmt[i])
            i++;
        
        return i;
    }
}