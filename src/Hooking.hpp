#pragma once
#include "common.hpp"
#include "Hooking/IHook.hpp"
#include "Util/Joaat.hpp"
#include "Util/MinHook.hpp"

namespace Spyral
{
    class Hooking final
    {
    private:
        Hooking();

    public:
        ~Hooking();

        Hooking(const Hooking&) = delete;
		Hooking(Hooking&&) noexcept = delete;
		Hooking& operator=(const Hooking&) = delete;
		Hooking& operator=(Hooking&&) noexcept = delete;

        /**
         * @brief Disable all hooks and do our cleanup
         * 
         */
        static void Destroy();
        /**
         * @brief Create and enable our hooks
         * 
         */
        static void Init();

        /**
         * @brief Get the Hook object
         * 
         * @tparam T Detour Type
         * @param name Identifying name of the hook
         * @return T Hook instance
         */
        template<typename T>
        static T GetHook(const std::string_view name);

    private:
        bool AddHook(const std::string_view name, std::unique_ptr<IHook>&& hook);

        void DestroyImpl();
        void InitImpl();

        static Hooking& GetInstance()
        {
            static Hooking i{};

            return i;
        }

    private:
        std::map<joaat_t, std::unique_ptr<IHook>> m_Hooks;

        bool m_Enabled;

        MinHook m_minhook;

    };

    template<typename T>
    inline T Hooking::GetHook(const std::string_view name)
    {
        const auto& i = GetInstance();
        const auto hash = Joaat(name);

        if (const auto& it = i.m_Hooks.find(hash); it != i.m_Hooks.end())
            return reinterpret_cast<T>(it->second.get());
        return nullptr;
    }
}