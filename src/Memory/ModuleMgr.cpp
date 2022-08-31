#include "ModuleMgr.hpp"
#include "Module.hpp"

namespace Spyral
{
    bool ModuleMgr::CacheModule(const std::string_view moduleName)
    {
        return GetInstance().CacheModuleImpl(moduleName);
    }

    bool ModuleMgr::CacheModuleImpl(const std::string_view moduleName)
    {
        return m_Modules.insert({ Hash(moduleName), std::make_unique<Module>(moduleName) }).second;
    }

    Module* ModuleMgr::GetModule(const std::string_view moduleName)
    {
        return GetInstance().GetModuleImpl(moduleName);
    }

    Module* ModuleMgr::GetModuleImpl(const std::string_view moduleName)
    {
        if (const auto &it = m_Modules.find(Hash(moduleName)); it != m_Modules.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

    void ModuleMgr::Init()
    {
        GetInstance().InitImpl();
    }

    void ModuleMgr::InitImpl()
    {
        for (const auto& mod : m_Modules | std::views::values)
        {
            if (mod->Loaded())
                continue;

            if (mod->TryGetModule())
            {
                // Successfully loaded

                continue;
            }
            // Failed to load
        }
    }
}