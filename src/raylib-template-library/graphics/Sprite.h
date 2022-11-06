//
// Created by robin on 30.10.22.
//

#ifndef GAME_DEV_TEMPLATE_SPRITE_H
#define GAME_DEV_TEMPLATE_SPRITE_H

#include "raylib-cpp.hpp"
#include "../../gamedev-base/GameDevBase.h"

namespace ggj
{

    class Sprite : public ggj::IGameObject<raylib::Vector2>
    {
        public:
            Sprite() = default;
            Sprite(const raylib::Vector2 &position, const raylib::Rectangle &drawingRect, raylib::Texture * texture, bool isVisible = true)
            : m_position {position}, m_drawingRect {drawingRect}, m_texture {texture},
              m_origin {drawingRect.width / 2, drawingRect.height / 2}
            {
                m_isVisible = true;
            }

            void rotate(float degrees) override;
            void scale(float scale) override;
            void move(const raylib::Vector2 &toMove) override;

            void update(float timeDelta) override;
            void draw() override;

        private:
            raylib::Texture *m_texture {nullptr};
            raylib::Rectangle m_drawingRect;

            raylib::Vector2 m_position {};
            raylib::Vector2 m_origin {};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_SPRITE_H
