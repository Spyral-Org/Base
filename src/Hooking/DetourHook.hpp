#pragma once
#include "../common.hpp"
#include "IHook.hpp"

namespace Spyral
{
    class DetourHook final : public IHook
    {
    public:
        DetourHook(const std::string_view name, void* target, void* detour);
        virtual ~DetourHook() override;

        virtual const std::string_view Name() const override;
        virtual bool Enable() override;
        virtual bool Disable() override;
        virtual bool IsEnabled() const override;

        bool EnableNow();
        bool DisableNow();

        template<typename T>
        T Original() const;

    private:
        void FixHook();

    private:
        const std::string_view m_Name;
        
        void* m_Target;
        void* m_Detour;

        void* m_Original;

        bool m_IsEnabled;

    };

    template<typename T>
    inline T DetourHook::Original() const
    {
        return reinterpret_cast<T>(m_Original);
    }
}