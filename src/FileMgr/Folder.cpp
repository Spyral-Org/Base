#include "Folder.hpp"
#include "FileMgr.hpp"

namespace Spyral
{
    Folder::Folder(std::filesystem::path&& path) :
        BaseExplorerItem(std::move(path))
    {

    }
}
