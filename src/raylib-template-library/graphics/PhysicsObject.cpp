//
// Created by robin on 30.10.22.
//

#include "PhysicsObject.h"

namespace dev
{
    void PhysicsObject::rotate(float degrees)
    {
        m_rotation += degrees;
    }

    void PhysicsObject::scale(float scale)
    {
        m_scale += scale;
    }

    void PhysicsObject::move(const raylib::Vector2 &toMove)
    {
        m_position += toMove;
    }

    void PhysicsObject::update(float timeDelta)
    {
        if(m_body != nullptr)
        {
            m_position = ConvertToVector2(m_body->GetPosition());
            m_rotation = ConvertToDegrees(m_body->GetAngle());
        }
    }

    void PhysicsObject::draw()
    {
        if(!m_isVisible)
            return;
        
        if(m_body != nullptr)
        {
            if(m_shape == PhysicsShape::Rectangle)
            {
                DrawRectanglePro(raylib::Rectangle(m_position.x, m_position.y, m_size.x, m_size.y), m_origin, m_rotation, m_color);
            }
            else if(m_shape == PhysicsShape::Circle)
            {
                DrawCircle((int32_t)m_position.x, (int32_t)m_position.y, m_size.x, m_color);
            }
        }
    }

    b2Vec2 PhysicsObject::ConvertToB2Vec2(const raylib::Vector2 &vector)
    {
        return {vector.x/PPM, vector.y/PPM};
    }

    raylib::Vector2 PhysicsObject::ConvertToVector2(const b2Vec2 &vec2)
    {
        return {vec2.x * PPM, vec2.y * PPM};
    }

    float PhysicsObject::ConvertToDegrees(float radians)
    {
        return radians * (180.0/PI);
    }
} // dev