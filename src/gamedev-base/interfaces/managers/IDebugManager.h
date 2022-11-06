//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_IDEBUGMANAGER_H
#define GAME_DEV_TEMPLATE_IDEBUGMANAGER_H

#include <cstdint>
#include "../../system/Colori.hpp"

namespace dev
{
    class IDebugManager
    {
        public:
            /*!
             * Pure virtual class needs virtual destructor so derived classes can call their own destructors
            */
            virtual ~IDebugManager() noexcept = default;

            virtual void clearText() = 0;
            virtual void setText(uint16_t line, const std::string &text, const dev::Colori &color = {255, 255, 255, 255}) = 0;
            virtual bool initialize() = 0;
            virtual void update(float timeDelta) = 0;
            virtual void draw() = 0;
    };
}

#endif //GAME_DEV_TEMPLATE_IDEBUGMANAGER_H
