#include "Hooking.hpp"
#include "Hooking/VMTHook.hpp"
#include "Pointers.hpp"

namespace Spyral
{
    Hooking::Hooking()
    {
        AddHook(std::make_unique<VMTHook>("DXPresent", Pointers::SwapChain));
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

    bool Hooking::AddHook(std::unique_ptr<IHook>&& hook)
    {
        return m_Hooks.insert({ Joaat(hook->Name()), std::move(hook) }).second;
    }
}