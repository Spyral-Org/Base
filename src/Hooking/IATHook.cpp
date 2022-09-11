#include "IATHook.hpp"

namespace Spyral
{
    IATHook::IATHook(const std::string_view name, void** iatAddr, void* detour) :
        m_Name(name),
        m_IATAddr(iatAddr),
        m_Detour(detour),
        m_Original(*iatAddr),
        m_Enabled(false),
        m_OldProtect(0)
    {

    }

    const std::string_view IATHook::Name() const
    {
        return m_Name;
    }

    bool IATHook::Enable()
    {
        if (m_Enabled)
            return false;

        if (!VirtualProtect(m_IATAddr, sizeof(void*), PAGE_READWRITE, reinterpret_cast<DWORD*>(&m_OldProtect)))
            return false;
        *m_IATAddr = m_Detour;
        VirtualProtect(m_IATAddr, sizeof(void*), m_OldProtect, nullptr);

        m_Enabled = true;
        return true;
    }

    bool IATHook::Disable()
    {
        if (!m_Enabled)
            return false;
        
        if (!VirtualProtect(m_IATAddr, sizeof(void*), PAGE_READWRITE, reinterpret_cast<DWORD*>(&m_OldProtect)))
            return false;
        *m_IATAddr = m_Original;
        VirtualProtect(&m_IATAddr, sizeof(void*), m_OldProtect, nullptr);

        m_Enabled = false;
        return true;
    }

    bool IATHook::IsEnabled() const
    {
        return m_Enabled;
    }
}