#pragma once
#include "../common.hpp"

namespace Spyral
{
    class Module final
    {
    public:
        Module(const std::string_view moduleName);

        [[nodiscard]] const char* const Name() const;
        [[nodiscard]] std::uintptr_t Base() const;
        [[nodiscard]] std::uintptr_t End() const;
        [[nodiscard]] std::uintptr_t Size() const;
        [[nodiscard]] bool Loaded() const;

        void* GetExport(const std::string_view symbolName) const;
        void* GetImport(const std::string_view symbolName) const;
        bool TryGetModule();

    private:
        const std::string_view m_Module;

        std::uintptr_t m_Base;
        std::uintptr_t m_Size;

        bool m_Loaded;

    };
}