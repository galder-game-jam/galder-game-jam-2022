//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_FRAME_HPP
#define GAME_DEV_TEMPLATE_FRAME_HPP

#include "raylib-cpp.hpp"

namespace ggj
{

    struct Frame
    {
        raylib::Vector2 position{};
        /*!
         * Lifetime for the frame in milliseconds
         */
        float time{};
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_FRAME_HPP
