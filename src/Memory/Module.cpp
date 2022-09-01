#include "Module.hpp"
#include <string.h>

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

    void* Module::GetImport(const std::string_view symbolName) const
    {
        if (!m_Loaded)
            return nullptr;

        const auto dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(m_Base);
        const auto ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(m_Base + dosHeader->e_lfanew);
        const auto importsDirectory = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

        for (auto importDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(m_Base + importsDirectory.VirtualAddress);
            importDescriptor->Name;
            importDescriptor++)
        {
            const auto firstThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(m_Base + importDescriptor->FirstThunk);
            const auto origThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(m_Base + importDescriptor->OriginalFirstThunk);

            for (auto firstThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(m_Base + importDescriptor->FirstThunk),
                origThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(m_Base + importDescriptor->OriginalFirstThunk);
                origThunk->u1.AddressOfData;
                firstThunk++, origThunk++)
            {
                const auto importData = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(m_Base + origThunk->u1.AddressOfData);

                if (strcmp(importData->Name, symbolName.data()) == 0)
                {
                    return &firstThunk->u1.Function;
                }
            }
        }
        return nullptr;
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