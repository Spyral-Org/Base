#pragma once
#include "../common.hpp"

namespace Spyral
{
    class BaseExplorerItem
    {
    public:
        BaseExplorerItem(std::filesystem::path&& path);

        [[nodiscard]] bool Exists() const;
        const std::filesystem::path& Path() const;

    protected:
        const std::filesystem::path m_Path;

    };
}
