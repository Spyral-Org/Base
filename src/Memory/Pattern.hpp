#pragma once
#include "../common.hpp"

namespace Spyral
{
    class Pattern final
    {
    public:
        Pattern(const std::string_view pattern);

        std::vector<std::uint8_t>& Get();

    private:
        std::vector<std::uint8_t> m_Pattern;

    };
}