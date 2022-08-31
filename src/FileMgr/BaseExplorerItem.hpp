#pragma once
#include "../common.hpp"
#include "FileMgr.hpp"

namespace Spyral
{
    class BaseExplorerItem
    {
    public:
        BaseExplorerItem(std::filesystem::path&& path) :
            m_Path(path)
        {

        }

        [[nodiscard]] bool Exists() const
        {
            return exists(m_Path);
        }

        const std::filesystem::path& Path() const
        {
            return m_Path;
        }

        template<typename T>
        T Move(std::filesystem::path newPath)
        {
            if (newPath.is_relative())
                newPath = m_Path.parent_path() / newPath;

            FileMgr::EnsureFileCanBeCreated(newPath);

            if (std::filesystem::exists(m_Path))
                std::filesystem::rename(m_Path, newPath);

            return { std::move(newPath) };
        }

    private:
        const std::filesystem::path m_Path;

    };
}