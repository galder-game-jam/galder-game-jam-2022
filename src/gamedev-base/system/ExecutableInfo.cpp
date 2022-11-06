//
// Created by robin on 27.10.22.
//

#include <atomic>
#include "ExecutableInfo.h"

namespace ggj
{
    std::filesystem::path ExecutableInfo::getExecutablePath()
    {
        #if defined(_MSC_VER)
        wchar_t path[FILENAME_MAX] = { 0 };
        GetModuleFileNameW(nullptr, path, FILENAME_MAX);
        return std::filesystem::path(path);
        #else
        char path[FILENAME_MAX];
        ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
        return std::filesystem::path(std::string(path, (count > 0) ? count: 0));
        #endif
    }

    std::filesystem::path ExecutableInfo::getExecutableDirectory()
    {
        #if defined(_MSC_VER)
        wchar_t path[FILENAME_MAX] = { 0 };
        GetModuleFileNameW(nullptr, path, FILENAME_MAX);
        return std::filesystem::path(path).parent_path();
        #else
        char path[FILENAME_MAX];
        ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
        return std::filesystem::path(std::string(path, (count > 0) ? count: 0)).parent_path();
        #endif
    }

    std::filesystem::path ExecutableInfo::getContentRootDirectory()
    {
        if(m_contentRoot.empty())
            return getExecutableDirectory() / "content";

        return m_contentRoot;
    }

    void ExecutableInfo::setContentRootDirectory(const std::filesystem::path &path)
    {
        m_contentRoot = path;
    }
} // dev