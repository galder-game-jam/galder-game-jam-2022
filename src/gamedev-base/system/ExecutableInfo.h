//
// Created by robin on 27.10.22.
//

#ifndef GAME_DEV_TEMPLATE_EXECUTABLEINFO_H
#define GAME_DEV_TEMPLATE_EXECUTABLEINFO_H

#include "../../gamedev-base/GameDevBase.h"
#include <filesystem>
namespace ggj
{

    class ExecutableInfo : public IExecutableInfo
    {
        public:
            ExecutableInfo() = default;

            void setContentRootDirectory(const std::filesystem::path &path) override;

            std::filesystem::path getExecutablePath() override;
            std::filesystem::path getExecutableDirectory() override;
            std::filesystem::path getContentRootDirectory() override;

        private:
            std::filesystem::path m_contentRoot {};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_EXECUTABLEINFO_H
