#pragma once
#include "../common.hpp"
#include "../Util/Hash.hpp"
#include "Module.hpp"

namespace Spyral
{
    class ModuleMgr final
    {
    private:
        ModuleMgr() {};

    public:
        ~ModuleMgr() = default;

        ModuleMgr(const ModuleMgr&) = delete;
		ModuleMgr(ModuleMgr&&) noexcept = delete;
		ModuleMgr& operator=(const ModuleMgr&) = delete;
		ModuleMgr& operator=(ModuleMgr&&) noexcept = delete;

        static bool CacheModule(const std::string_view moduleName);
        static Module* GetModule(const std::string_view moduleName);

        static void Init();

    private:
        bool CacheModuleImpl(const std::string_view moduleName);
        Module* GetModuleImpl(const std::string_view moduleName);

        void InitImpl();

        static ModuleMgr& GetInstance()
        {
            static ModuleMgr i {};

            return i;
        }

    private:
        std::map<hash, std::unique_ptr<Module>> m_Modules;

    };
}