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
        return m_Modules.insert({ Joaat(moduleName), std::make_unique<Module>(moduleName) }).second;
    }

    Module* ModuleMgr::GetModule(const std::string_view moduleName)
    {
        return GetInstance().GetModuleImpl(moduleName);
    }

    Module* ModuleMgr::GetModuleImpl(const std::string_view moduleName)
    {
        if (const auto &it = m_Modules.find(Joaat(moduleName)); it != m_Modules.end())
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
                LOG(G3LOG_DEBUG) << "Found module [" << mod->Name() << "]\t @ [" << HEX(mod->Base()) << "]\t : sizeof[" << std::size_t(mod->Size()) << "]";

                continue;
            }
            
            LOG(WARNING) << "Unable to find '" << mod->Name() << "' in the current process!";
        }
    }
}