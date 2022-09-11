#include "DetourHook.hpp"
#include "MinHook.h"
#include "../Memory/AddressHelper.hpp"

namespace Spyral
{
    DetourHook::DetourHook(const std::string_view name, void* target, void* detour) :
        m_Name(name),
        m_Target(target),
        m_Detour(detour),
        m_Original(nullptr),
        m_IsEnabled(false)
    {
        FixHook();

        if (const auto result = MH_CreateHook(m_Target, m_Detour, &m_Original); result != MH_OK)
        {
            throw std::runtime_error("Failed to create hook.");
        }
    }

    DetourHook::~DetourHook()
    {
        if (m_Target)
        {
            MH_RemoveHook(m_Target);
        }
    }

    const std::string_view DetourHook::Name() const
    {
        return m_Name;
    }

    bool DetourHook::Enable()
    {
        if (m_IsEnabled)
            return false;
        if (const auto result = MH_QueueEnableHook(m_Target); result != MH_OK)
        {
            LOG(WARNING) << "Failed to queue hook '" << m_Name << "' to be enabled.";

            return false;
        }

        m_IsEnabled = true;
        return true;
    }

    bool DetourHook::Disable()
    {
        if (!m_IsEnabled)
            return false;
        if (const auto result = MH_QueueDisableHook(m_Target); result != MH_OK)
        {
            LOG(WARNING) << "Failed to queue hook '" << m_Name << "' to be disabled.";

            return false;
        }

        m_IsEnabled = false;
        return true;
    }

    bool DetourHook::EnableNow()
    {
        if (m_IsEnabled)
            return false;
        if (const auto result = MH_EnableHook(m_Target); result != MH_OK)
        {
            LOG(WARNING) << "Failed to enable hook '" << m_Name << "'";

            return false;
        }

        m_IsEnabled = true;
        return true;
    }

    bool DetourHook::DisableNow()
    {
        if (m_IsEnabled)
            return false;
        if (const auto result = MH_DisableHook(m_Target); result != MH_OK)
        {
            LOG(WARNING) << "Failed to disable hook '" << m_Name << "'";

            return false;
        }

        m_IsEnabled = true;
        return true;
    }

    bool DetourHook::IsEnabled() const
    {
        return m_IsEnabled;
    }

    void DetourHook::FixHook()
    {
        auto ptr = AddressHelper(m_Target);
        while(*ptr.As<uint8_t*>() == 0xE9)
        {
            ptr = ptr.Add(1).Relative();
        }
        m_Target = ptr.As<void*>();
    }
}