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

        if(m_isDead)
        {
            m_isDead = false;
            m_body->SetTransform(ConvertToB2Vec2(m_startPos), m_body->GetAngle());
        }
        PhysicsObject::update(timeDelta);

        handleInputs(timeDelta);
        m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});


        if(m_animation.isValid())
        {
            m_animation.update(timeDelta);
            m_drawingRect = m_animation.getDrawingRect();
        }
    }

    void Player::handleInputs(float timeDelta)
    {
        //Should have a collection of commands or something assigned to the player for a best practice approach
        //But this is just meant to be a quick example
        b2Vec2 vel = m_body->GetLinearVelocity();
        m_velocity = raylib::Vector2{vel.x, vel.y};
        if(m_inputManager.keyDown(KeyboardKey::A) && !m_inputManager.keyDown(KeyboardKey::D))
        {
            m_flip = true;
            m_velocity = raylib::Vector2{m_velocity.x - (10.f * timeDelta), m_velocity.y};
            if(m_velocity.y < 0.2f && m_velocity.y > -0.2f)
                setPlayerState(PlayerState::Walk);
        }
        else if(m_inputManager.keyDown(KeyboardKey::D) && !m_inputManager.keyDown(KeyboardKey::A))
        {
            m_flip = false;
            m_velocity = raylib::Vector2{m_velocity.x + (10.f * timeDelta), m_velocity.y};
            if(m_velocity.y < 0.2f && m_velocity.y > -0.2f)
                setPlayerState(PlayerState::Walk);
        }
        else
        {
            m_velocity = raylib::Vector2{0.f, m_velocity.y};
        }

        //Jump
        if(m_inputManager.keyPressed(KeyboardKey::W) && m_jumps < m_maxJumps)
        {
            ++m_jumps;
            m_velocity = raylib::Vector2{m_velocity.x, m_velocity.y - 5.f};
        }

        #ifdef GAME_DEV_DEBUG
        if(m_inputManager.keyPressed(KeyboardKey::F9))
        {
            if(m_maxJumps == 2)
                m_maxJumps = 10000;
            else
                m_maxJumps = 2;
        }
        //Toggle camera-follow
        if(m_inputManager.keyPressed(KeyboardKey::Enter))
        {
            m_cameraShouldFollowPlayer = !m_cameraShouldFollowPlayer;
        }
        #endif

        //Toggle player rotate. Fun!
        if(m_inputManager.keyPressed(KeyboardKey::Space))
        {
            bool rotationFixedToggle = !m_body->IsFixedRotation();
            m_body->SetFixedRotation(rotationFixedToggle);
            if(rotationFixedToggle)
                m_body->SetTransform(m_body->GetPosition(), 0);
        }


        if(m_velocity.x == 0 && m_velocity.y == 0)
        {
            setPlayerState(PlayerState::Idle);
        }
        else if(m_velocity.y > 0.2f)
        {
            setPlayerState(PlayerState::Fall);
        }
        else if(m_velocity.y < -0.2f)
        {
            setPlayerState(PlayerState::Jump);
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

    void Player::setPlayerState(PlayerState playerState)
    {
        if (m_playerState == playerState)
            return;

        m_playerState = playerState;
        m_animation = m_animationManager.getAnimation(m_mapper.getAnimationNameByPlayerState(playerState));
    }

    void Player::beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact)
    {
        b2Manifold *manifold = contact->GetManifold();
        b2WorldManifold worldManifold;
        contact->GetWorldManifold(&worldManifold); //Required to calculate manifold when circle hits circle

        if(manifold->localNormal.y < -0.8f || worldManifold.normal.y > 0.5f)
            m_jumps = 0;

        if(b->getUserData()->getObjectType() == ObjectType::Enemy)
        {
            m_isDead = true;
        }
        if(b->getUserData()->getCommand() == "clear_level")
        {
            m_hasClearedLevel = true;
        }
    }

    bool Player::hasClearedLevel() const
    {
        return m_hasClearedLevel;
    }

    void Player::setHasClearedLevel(bool hasClearedLevel)
    {
        m_hasClearedLevel = hasClearedLevel;
    }
} // dev