#pragma once
#include "../common.hpp"
#include "Module.hpp"
#include "Pattern.hpp"

namespace Spyral
{
    using PatternCallback = std::function<bool(void*)>;
    class PatternScanner final
    {
    public:
        PatternScanner(const Module* module);

        void Add(const std::string_view pattern, PatternCallback&& cb);
        bool Scan();

        static void* ScanNow(const Module* module, Pattern& pattern);

    private:
        const Module* m_Module;
        std::vector<std::pair<Pattern, PatternCallback>> m_Patterns;

    };
}