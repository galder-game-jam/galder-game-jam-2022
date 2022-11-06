//
// Created by robin on 05.11.22.
//

#include "Player.h"

namespace ggj
{
    void Player::draw()
    {
        PhysicsSprite::draw();
    }

    void Player::update(float timeDelta)
    {
        if(m_body == nullptr)
            return;

        PhysicsObject::update(timeDelta);

        handleInputs(timeDelta);
        m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});
    }

    void Player::handleInputs(float timeDelta)
    {
        //Should have a collection of commands or something assigned to the player for a best practice approach
        //But this is just meant to be a quick example
        b2Vec2 vel = m_body->GetLinearVelocity();
        m_velocity = {vel.x, vel.y};
        if(m_inputManager.keyDown(KeyboardKey::A) && !m_inputManager.keyDown(KeyboardKey::D))
        {
            m_flip = true;
            m_velocity = {m_velocity.x - (10.f * timeDelta), m_velocity.y};
        }
        else if(m_inputManager.keyDown(KeyboardKey::D) && !m_inputManager.keyDown(KeyboardKey::A))
        {
            m_flip = false;
            m_velocity = {m_velocity.x + (10.f * timeDelta), m_velocity.y};
        }
        else
            m_velocity = {0.f, m_velocity.y};

        //Jump
        if(m_inputManager.keyPressed(KeyboardKey::W))
            m_velocity = {m_velocity.x, m_velocity.y - 5.f};

        //Toggle player rotate. Fun!
        if(m_inputManager.keyPressed(KeyboardKey::Space))
        {
            bool rotationFixedToggle = !m_body->IsFixedRotation();
            m_body->SetFixedRotation(rotationFixedToggle);
            if(rotationFixedToggle)
                m_body->SetTransform(m_body->GetPosition(), 0);
        }

        //Toggle camera-follow
        if(m_inputManager.keyPressed(KeyboardKey::Enter))
        {
            m_cameraShouldFollowPlayer = !m_cameraShouldFollowPlayer;
        }
    }

    const Vector2 &Player::getVelocity() const
    {
        return m_velocity;
    }

    bool Player::cameraShouldFollowPlayer() const
    {
        return m_cameraShouldFollowPlayer;
    }
} // dev