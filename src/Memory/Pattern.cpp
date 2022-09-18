#include "Pattern.hpp"

namespace Spyral
{
    Pattern::Pattern(const std::string_view name, const std::string_view pattern)
        : m_Name(name)
    {
        for (std::size_t i = 0; i < pattern.length(); i++)
        {
            if (pattern[i] == ' ')
                continue;

            if (pattern[i] == '?')
            {
                if (pattern[i + 1] == '?')
                    i++;

                m_Pattern.push_back(0);

                continue;
            }

            const char opcode[] = { pattern[i], pattern[i + 1] };
            const auto binaryOpcode = strtoull(opcode, nullptr, 16);

            m_Pattern.push_back(static_cast<std::uint8_t>(binaryOpcode));

            i++;
        }
    }

    std::vector<std::uint8_t>& Pattern::Get()
    {
        return m_Pattern;
    }

    const std::string_view Pattern::Name() const
    {
        return m_Name;
    }
}