#include "PatternScanner.hpp"

namespace Spyral
{
    PatternScanner::PatternScanner(const Module* module) : 
        m_Module(module),
        m_Patterns()
    {

    }

    void PatternScanner::Add(const std::string_view name, const std::string_view pattern, PatternCallback&& cb)
    {
        m_Patterns.push_back({ { name, pattern }, cb });
    }

    bool PatternScanner::Scan()
    {
        for (auto& [ pattern, callback ] : m_Patterns)
        {
            if (const auto addr = PatternScanner::ScanNow(m_Module, pattern); addr && callback(addr))
                continue;
            
            return false;
        }
        return true;
    }

    void* PatternScanner::ScanNow(const Module* module, Pattern &pattern)
    {
        const auto patternBytes = pattern.Get();
        for (std::uintptr_t i = module->Base(); i < module->End(); i++)
        {
            if (patternBytes.size() > module->End() - i)
                break;

            const auto opcode = reinterpret_cast<std::uint8_t*>(i);
            bool found = true;
            for (std::size_t opIdx = 0; opIdx < patternBytes.size() && found; opIdx++)
            {
                if (patternBytes[opIdx] && patternBytes[opIdx] != opcode[opIdx])
                {
                    found = false;
                }
            }
            
            if (found)
            {
                LOG(G3LOG_DEBUG) << "Found pattern [" << pattern.Name() << "] @ " << HEX(i);

                return reinterpret_cast<void*>(i);
            }
        }

        LOG(WARNING) << "Failed to find pattern [" << pattern.Name() << "]!";
        return nullptr;
    }
}