//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_DEBUGMANAGER_H
#define GAME_DEV_TEMPLATE_DEBUGMANAGER_H

#include "../../gamedev-base/GameDevBase.h"
#include "raylib-cpp.hpp"
#include <map>
namespace ggj
{

    class DebugManager : public ggj::IDebugManager
    {
        public:
            void setText(uint16_t line, const std::string &text, const Colori &color) override;
            bool initialize() override;
            void clearText() override;
            void update(float timeDelta) override;
            void draw() override;

        private:
            std::map<uint16_t, std::pair<std::string, Colori>> m_debugTexts {};
            int32_t m_fontSize {20};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_DEBUGMANAGER_H
