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

namespace ggj
{

    class PhysicsSprite : public PhysicsObject
    {
        public:
            PhysicsSprite() = default;
            PhysicsSprite(b2Body *body, const raylib::Vector2 &physicsSize, const raylib::Vector2 &spriteSize, const raylib::Rectangle &drawingRect, raylib::Texture * texture, bool isVisible = true)
            : PhysicsObject(body, physicsSize, (body->GetFixtureList()[0].GetShape()->GetType() == b2Shape::e_circle) ? PhysicsShape::Circle : PhysicsShape::Rectangle, isVisible),
              m_spriteSize{spriteSize}, m_drawingRect {drawingRect}, m_texture {texture}
            {
                if(m_shape == PhysicsShape::Circle)
                    m_origin = raylib::Vector2(spriteSize.x / 2, spriteSize.y - physicsSize.y);
                else
                    m_origin = raylib::Vector2(spriteSize.x / 2, spriteSize.y - physicsSize.y / 2);
            }
            void draw() override;

        protected:
            raylib::Texture *m_texture {nullptr};
            raylib::Rectangle m_drawingRect;
            bool m_flip {false};
            raylib::Vector2 m_spriteSize {0.f, 0.f};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_PHYSICSSPRITE_H
