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
        if (!m_Loaded)
            return nullptr;

        const auto dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(m_Base);
        const auto ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(m_Base + dosHeader->e_lfanew);
        const auto imageDataDirectory = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
        const auto exportDirectory = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(m_Base + imageDataDirectory.VirtualAddress);

        const auto nameOffsetArray = reinterpret_cast<DWORD*>(m_Base + exportDirectory->AddressOfNames);
        const auto ordinalArray = reinterpret_cast<WORD*>(m_Base + exportDirectory->AddressOfNameOrdinals);
        const auto functionOffsetArray = reinterpret_cast<DWORD*>(m_Base + exportDirectory->AddressOfFunctions);

        for (std::size_t i = 0; i < exportDirectory->NumberOfFunctions; i++)
        {
            const auto functionName = reinterpret_cast<const char*>(m_Base + nameOffsetArray[i]);
            if (strcmp(functionName, symbolName.data()))
                continue;
            
            return functionOffsetArray + ordinalArray[i];
        }
        return nullptr;
    }

    void* Module::GetImport(const std::string_view symbolName) const
    {
        if (!m_Loaded)
            return nullptr;

        const auto dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(m_Base);
        const auto ntHeader = reinterpret_cast<IMAGE_NT_HEADERS*>(m_Base + dosHeader->e_lfanew);
        const auto imageDataDirectory = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

        for (auto importDescriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(m_Base + imageDataDirectory.VirtualAddress);
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