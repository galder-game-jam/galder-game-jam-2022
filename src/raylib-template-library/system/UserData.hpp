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
            UserData(ObjectType objectType, const raylib::Vector2 &force, const std::string command): m_objectType{objectType}, m_force{force}, m_command {command}
            {
            }

            void destroy() { m_shouldBeDestroyed = true; };

            ObjectType getObjectType() const { return m_objectType; }
            const raylib::Vector2 &getForce() const { return m_force; }
            bool shouldBeDestroyed() const { return m_shouldBeDestroyed; }
            const std::string &getCommand() const { return m_command; }

        private:
            ObjectType m_objectType {ObjectType::Undefined};
            raylib::Vector2 m_force {0.f, 0.f};
            bool m_shouldBeDestroyed{false};
            std::string m_command{};
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_USERDATA_HPP
