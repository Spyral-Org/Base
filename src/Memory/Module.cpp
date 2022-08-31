#include "Module.hpp"
#include <libloaderapi.h>

namespace Spyral
{
    Module::Module(const std::string_view moduleName) :
        m_Module(moduleName),
        m_Base(0),
        m_Size(0),
        m_Loaded(false)
    {

    }

    const char* const Module::Name() const
    {
        return m_Module.data();
    }

    std::uintptr_t Module::Base() const
    {
        return m_Base;
    }

    std::uintptr_t Module::End() const
    {
        return m_Base + m_Size;
    }

    std::uintptr_t Module::Size() const
    {
        return m_Size;
    }

    bool Module::Loaded() const
    {
        return m_Loaded;
    }

    void* Module::GetExport(const std::string_view symbolName) const
    {
        return reinterpret_cast<void*>(
            GetProcAddress(reinterpret_cast<HMODULE>(m_Base), symbolName.data()));
    }

    bool Module::TryGetModule()
    {
        m_Base = reinterpret_cast<std::uintptr_t>(GetModuleHandleA(m_Module.data()));
        if (m_Base == 0)
            return false;
        
        const auto dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(m_Base);
        const auto ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(m_Base + dosHeader->e_lfanew);

        m_Size = ntHeader->OptionalHeader.SizeOfCode;
        m_Loaded = true;

        return true;
    }
}