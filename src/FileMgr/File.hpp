#pragma once
#include "../common.hpp"
#include "BaseExplorerItem.hpp"

namespace Spyral
{
    class File final : public BaseExplorerItem
    {
    public:
        File(std::filesystem::path&& path);

        File Move(const std::filesystem::path& newPath)
        {
            return BaseExplorerItem::Move<File>(newPath);
        }
    };
}