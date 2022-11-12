//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_USERDATA_HPP
#define GAME_DEV_TEMPLATE_USERDATA_HPP

#include "raylib-cpp.hpp"
#include "../enums/ObjectType.h"

namespace ggj
{

    class UserData
    {
        public:
            UserData() = default;
            UserData(ObjectType objectType, const raylib::Vector2 &force): m_objectType{objectType}, m_force{force}
            {
            }

            void destroy() { m_shouldBeDestroyed = true; };

            ObjectType getObjectType() const { return m_objectType; }
            const raylib::Vector2 &getForce() const { return m_force; }
            bool shouldBeDestroyed() const { return m_shouldBeDestroyed; }

        private:
            ObjectType m_objectType {ObjectType::Undefined};
            raylib::Vector2 m_force {0.f, 0.f};
            bool m_shouldBeDestroyed{false};
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_USERDATA_HPP
