//
// Created by robin on 30.10.22.
//

#include "Sprite.h"

namespace ggj
{
    void Sprite::rotate(float degrees)
    {
        m_rotation += degrees;
    }

    void Sprite::scale(float scale)
    {
        m_scale += scale;
    }

    void Sprite::move(const raylib::Vector2 &toMove)
    {
        m_position += toMove;
    }

    void Sprite::update(float timeDelta)
    {

    }

    void Sprite::draw()
    {
        if(!m_isVisible || m_texture == nullptr)
            return;

        m_texture->Draw(m_drawingRect, raylib::Rectangle(m_position.x, m_position.y, m_drawingRect.width, m_drawingRect.height), m_origin, m_rotation, WHITE);
    }
} // dev