#pragma once
#include "BaseExplorerItem.hpp"

namespace Spyral
{
    class Folder final : public BaseExplorerItem
    {
    public:
        Folder(std::filesystem::path&& folder);
    };
}
