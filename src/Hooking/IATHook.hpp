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
        IATHook(const std::string_view name, void** iatAddr, void* detour);
        virtual ~IATHook() = default;

        virtual const std::string_view Name() const override;
        virtual bool Enable() override;
        virtual bool Disable() override;
        virtual bool IsEnabled() const override;

        template<typename T>
        T Original() const;

    private:
        const std::string_view m_Name;

        void** m_IATAddr;
        void* m_Detour;

        void* m_Original;

        bool m_Enabled;
        std::uint32_t m_OldProtect;

    };

    template<typename T>
    inline T IATHook::Original() const
    {
        return reinterpret_cast<T>(m_Original);
    }
}