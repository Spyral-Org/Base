#include "IATHook.hpp"

namespace Spyral
{
    IATHook::IATHook(const std::string_view name, void* target, void* detour) :
        m_Name(name),
        m_Target(target),
        m_Detour(detour),
        m_Original(target),
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

        if (!VirtualProtect(&m_Target, sizeof(m_Target), PAGE_READWRITE, reinterpret_cast<DWORD*>(&m_OldProtect)))
            return false;
        
        m_Target = m_Detour;

        m_Enabled = true;
        return true;
    }

    bool IATHook::Disable()
    {
        if (!m_Enabled)
            return false;
        
        m_Target = m_Original;
        VirtualProtect(&m_Target, sizeof(m_Target), m_OldProtect, nullptr);

        m_Enabled = false;
        return true;
    }

    bool IATHook::IsEnabled() const
    {
        return m_Enabled;
    }
}