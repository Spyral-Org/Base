#pragma once
#include "../common.hpp"
#include "IHook.hpp"

namespace Spyral
{
    class IATHook final : public IHook
    {
    private:
        /* data */
    public:
        IATHook(const std::string_view name, void* target, void* detour);
        virtual ~IATHook() = default;

        virtual const std::string_view Name() const override;
        virtual bool Enable() override;
        virtual bool Disable() override;
        virtual bool IsEnabled() const override;

    private:
        const std::string_view m_Name;

        void* m_Target;
        void* m_Detour;

        void* m_Original;

        bool m_Enabled;
        std::uint32_t m_OldProtect;

    };
    
}