//
// Created by robin on 27.10.22.
//

#include "ExecutableInfo.h"
#include <atomic>

#ifdef __clang__
    #include <libc.h>
    #include <mach-o/dyld.h>
#endif


//#if defined(_MSC_VER)
//#include <libloaderapi.h>
//#endif

namespace ggj
{
    std::filesystem::path ExecutableInfo::getExecutablePath()
    {
        #if defined(_MSC_VER)
        return std::filesystem::current_path(); //NOTE: This will just give the path to the executable folder, but is not in use for anything special, so wasn't prioritized!
        #elif __clang__
        char buf [PATH_MAX];
        uint32_t bufsize = PATH_MAX;
        if(!_NSGetExecutablePath(buf, &bufsize))
            puts(buf);

        std::filesystem::path path {buf};
        return path;
        #else
        char path[FILENAME_MAX];
        ssize_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
        return std::filesystem::path(std::string(path, (count > 0) ? count: 0));
        #endif
    }

    std::filesystem::path ExecutableInfo::getExecutableDirectory()
    {
        #if defined(_MSC_VER)
        return std::filesystem::current_path();
        #elif __clang__
        char buf [PATH_MAX];
        uint32_t bufsize = PATH_MAX;
        if(!_NSGetExecutablePath(buf, &bufsize))
            puts(buf);

        std::filesystem::path path {buf};
        return path.parent_path();
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