//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_IEXECUTABLEINFO_H
#define GAME_DEV_TEMPLATE_IEXECUTABLEINFO_H

#include <string>
#include <filesystem>
namespace dev
{
    class IExecutableInfo
    {
        public:
            virtual ~IExecutableInfo() noexcept = default;


            virtual void setContentRootDirectory(const std::filesystem::path &path) = 0;

            virtual std::filesystem::path getExecutablePath() = 0;
            virtual std::filesystem::path getExecutableDirectory() = 0;
            virtual std::filesystem::path getContentRootDirectory() = 0;
    };
}

#endif //GAME_DEV_TEMPLATE_IEXECUTABLEINFO_H
