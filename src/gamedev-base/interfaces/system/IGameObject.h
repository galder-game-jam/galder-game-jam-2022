//
// Created by robin on 30.10.22.
//

#ifndef GAME_DEV_TEMPLATE_IGAMEOBJECT_H
#define GAME_DEV_TEMPLATE_IGAMEOBJECT_H

#include "../../system/Vector2D.hpp"

namespace dev
{
    template <class T>
    class IGameObject
    {
        public:
            virtual ~IGameObject() noexcept = default;
            virtual void rotate(float degrees) = 0;
            virtual void scale(float scale) = 0;
            virtual void move(const T &toMove) = 0;

            [[nodiscard]] int32_t getLayer() const  { return m_layer; }
            T getPosition() const                   { return m_position; }
            [[nodiscard]] float getRotation() const { return m_rotation; }
            [[nodiscard]] float getScale() const    { return m_scale; }
            [[nodiscard]] bool isVisible() const    { return m_isVisible; }

            void setRotation(float rotation) { m_rotation = rotation; }
            void setScale(float scale) { m_scale = scale; }
            void setLayer(int32_t layer) { m_layer = layer; }
            void setPosition(const T &position) { m_position = position; }
            void setVisible(bool visible) { m_isVisible = visible; }

            virtual void update(float timeDelta) = 0;
            virtual void draw() = 0;

        protected:
            float m_rotation {};
            float m_scale {1.f};
            int32_t m_layer {};
            bool m_isVisible {};
            T m_position {};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_IGAMEOBJECT_H
