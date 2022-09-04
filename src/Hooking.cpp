#include "Hooking.hpp"

namespace Spyral
{
    Hooking::Hooking()
    {
        //AddHook("DX11Present", );
    }

    Hooking::~Hooking()
    {
        if (m_Enabled)
        {
            DestroyImpl();
        }
    }

    void Hooking::Destroy()
    {
        GetInstance().DestroyImpl();
    }

    void Hooking::DestroyImpl()
    {
        if (!m_Enabled)
            return;
        m_Enabled = false;

        for (auto& hook : m_Hooks | std::views::values)
            hook->Disable();

        m_minhook.ApplyQueued();
    }

    void Hooking::Init()
    {
        GetInstance().InitImpl();
    }

    void Hooking::InitImpl()
    {
        if (m_Enabled)
            return;
        m_Enabled = true;

        for (auto& hook : m_Hooks | std::views::values)
            hook->Enable();

        m_minhook.ApplyQueued();
    }

    bool Hooking::AddHook(const std::string_view name, std::unique_ptr<IHook>&& hook)
    {
        const auto hash = Joaat(name);

        return m_Hooks.insert({ hash, std::move(hook) }).second;
    }
}