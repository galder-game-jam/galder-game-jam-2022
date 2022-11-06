//
// Created by robin on 03.11.22.
//

#include "PhysicsSprite.h"

namespace dev
{
    void PhysicsSprite::draw()
    {
        if(m_texture == nullptr)
            PhysicsObject::draw();

        float width = (m_flip) ? -m_drawingRect.width : m_drawingRect.width;
        raylib::Rectangle rect = {m_drawingRect.x, m_drawingRect.y, width, m_drawingRect.height};
        m_texture->Draw(rect, raylib::Rectangle(m_position.x, m_position.y,  m_drawingRect.width, m_drawingRect.height), m_origin, m_rotation, WHITE);
    }
} // dev