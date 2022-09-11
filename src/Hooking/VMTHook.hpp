#pragma once
#include "IHook.hpp"

namespace Spyral
{
    class VMTHook final : public IHook
    {
    public:
        VMTHook(const std::string_view name, void*** vmtBaseAddr);
        ~VMTHook();

        virtual const std::string_view Name() const override;
        virtual bool Enable() override;
        virtual bool Disable() override;
        virtual bool IsEnabled() const override;

        template<typename T>
        T Original(const std::uint32_t idx) const;

        void Hook(const std::uint32_t idx, void* detour);
        void UnHook(const std::uint32_t idx);

        std::size_t VMTSize() const;

    private:
        /**
         * @brief Get the amount functions in the virtual method table
         * 
         * @return std::size_t 
         */
        static std::size_t GetVMTSize(void** vmt);

    private:
        const std::string_view m_Name;
        const std::size_t m_VMTSize;
        bool m_Enabled;

        void*** m_VMTBaseAddr;
        void** m_OriginalVMT;
        void** m_NewVMT;

    };

    template<typename T>
    inline T VMTHook::Original(const std::uint32_t idx) const
    {
        return reinterpret_cast<T>(m_OriginalVMT[idx]);
    }
}