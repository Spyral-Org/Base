#include "File.hpp"
#include "FileMgr.hpp"

namespace Spyral
{
    File::File(std::filesystem::path&& path) :
        BaseExplorerItem(std::move(path))
    {

    }

    File File::Move(std::filesystem::path newPath)
    {
        if (newPath.is_relative())
            newPath = m_Path.parent_path() / newPath;

        FileMgr::EnsureFileCanBeCreated(newPath);

        if (std::filesystem::exists(m_Path))
            std::filesystem::rename(m_Path, newPath);

        return { std::move(newPath) };
    }
}
