//
// Created by robin on 03.11.22.
//

#ifndef GAME_DEV_TEMPLATE_PHYSICSSPRITE_H
#define GAME_DEV_TEMPLATE_PHYSICSSPRITE_H

#include "raylib-cpp.hpp"
#include "box2d/box2d.h"
#include "../enums/PhysicsShape.h"
#include "../../gamedev-base/GameDevBase.h"
#include "PhysicsObject.h"

namespace dev
{

    class PhysicsSprite : public PhysicsObject
    {
        public:
            PhysicsSprite() = default;
            PhysicsSprite(b2Body *body, const raylib::Vector2 &size, const raylib::Rectangle &drawingRect, raylib::Texture * texture, bool isVisible = true)
            : PhysicsObject(body, size, (body->GetFixtureList()[0].GetShape()->GetType() == b2Shape::e_circle) ? PhysicsShape::Circle : PhysicsShape::Rectangle, isVisible),
              m_drawingRect {drawingRect}, m_texture {texture}
            {
                m_origin = raylib::Vector2(drawingRect.width / 2, drawingRect.height / 2);
            }
            void draw() override;

        protected:
            raylib::Texture *m_texture {nullptr};
            raylib::Rectangle m_drawingRect;
            bool m_flip {false};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_PHYSICSSPRITE_H
