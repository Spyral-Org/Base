#include "File.hpp"

namespace Spyral
{
    File::File(std::filesystem::path&& path) :
        BaseExplorerItem(std::move(path))
    {

    }
}