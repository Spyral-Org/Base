#pragma once
#include "../common.hpp"

namespace Spyral
{
    class Pattern final
    {
    public:
        Pattern(const std::string_view name, const std::string_view pattern);

        std::vector<std::uint8_t>& Get();
        const std::string_view Name() const;

    private:
        const std::string_view m_Name;
        std::vector<std::uint8_t> m_Pattern;

    };
}