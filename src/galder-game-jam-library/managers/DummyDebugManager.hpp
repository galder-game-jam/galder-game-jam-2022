//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_DUMMYDEBUGMANAGER_HPP
#define GAME_DEV_TEMPLATE_DUMMYDEBUGMANAGER_HPP

#include "../../gamedev-base/GameDevBase.h"

namespace ggj
{

    class DummyDebugManager : public ggj::IDebugManager
    {
        public:
            void clearText() override { }
            void setText(uint16_t line, const std::string &text, const Colori &color) override { }
            bool initialize() override { return true; }
            void update(float timeDelta) override { }
            void draw() override { }
    };

} // dev

#endif //GAME_DEV_TEMPLATE_DUMMYDEBUGMANAGER_HPP
