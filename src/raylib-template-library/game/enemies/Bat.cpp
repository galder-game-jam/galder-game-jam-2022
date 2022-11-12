//
// Created by soberga on 12.11.22.
//

#include "Bat.h"

namespace ggj
{
    void Bat::move(const raylib::Vector2 &toMove)
    {

    }

    void Bat::beginContact(PhysicsObject *a, PhysicsObject *b)
    {
        UserData* userDataB = b->getUserData();

        if(userDataB->getCommand() == "enemy_turn")
        {
            m_flip = !m_flip;
            m_velocity = -m_velocity;
        }
    }
} // ggj