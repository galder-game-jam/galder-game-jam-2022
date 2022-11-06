//
// Created by robin on 30.10.22.
//

#ifndef GAME_DEV_TEMPLATE_PHYSICSOBJECT_H
#define GAME_DEV_TEMPLATE_PHYSICSOBJECT_H

#include "raylib-cpp.hpp"
#include "box2d/box2d.h"
#include "../enums/PhysicsShape.h"
#include "../../gamedev-base/GameDevBase.h"

namespace dev
{
    class PhysicsObject : public dev::IGameObject<raylib::Vector2>
    {
        public:
            PhysicsObject() = default;
            PhysicsObject(b2Body *body, const raylib::Vector2 &size, PhysicsShape shape, raylib::Color color = raylib::Color::Red(), bool isVisible = true)
            : m_body {body}, m_size {size}, m_shape {shape}, m_origin {size.x / 2, size.y / 2}, m_color {color}
            {
                m_isVisible = isVisible;
            }
            void rotate(float degrees) override;
            void scale(float scale) override;
            void move(const raylib::Vector2 &toMove) override;

            void update(float timeDelta) override;
            void draw() override;

            //Static helpers
            static constexpr float PPM = 30.f;
            static b2Vec2 ConvertToB2Vec2(const raylib::Vector2 &vector);
            [[nodiscard]] static raylib::Vector2 ConvertToVector2(const b2Vec2 &vec2);
            static float ConvertToDegrees(float radians);

        protected:
            b2Body *m_body {nullptr};
            PhysicsShape m_shape {PhysicsShape::None};

            raylib::Vector2 m_size {};
            raylib::Vector2 m_origin {};
            raylib::Color m_color {};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_PHYSICSOBJECT_H
