//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_PLAYER_H
#define GAME_DEV_TEMPLATE_PLAYER_H

#include "../graphics/PhysicsSprite.h"
#include "../enums/KeyboardKey.h"
#include "../managers/AnimationManager.h"
#include "../enums/PlayerState.h"
#include "../interfaces/system/IMapper.h"


namespace ggj
{
    class Player : public PhysicsSprite
    {
        public:
            Player() = default;
            Player(ggj::IInputManager<ggj::KeyboardKey> &inputManager, ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animationManager, IMapper &mapper, b2Body *body, const raylib::Vector2 &physicsSize,
                   const raylib::Vector2 &spriteSize,
                   const raylib::Rectangle &drawingRect, raylib::Texture * texture, const UserData &userData, bool isVisible = true)
            : PhysicsSprite(body, physicsSize, spriteSize, drawingRect, texture, userData, isVisible), m_inputManager {inputManager}, m_animationManager {animationManager}, m_mapper{mapper}
            {
                m_body->SetFixedRotation(true);
                m_animation = m_animationManager.getAnimation(AnimationName::PlayerIdle);
                m_startPos = ConvertToVector2(m_body->GetPosition());
            }

            [[nodiscard]] const Vector2 &getVelocity() const;
            [[nodiscard]] bool cameraShouldFollowPlayer() const;

            void beginContact(PhysicsObject *a, PhysicsObject *b) override;

            void update(float timeDelta) override;
            void draw() override;

        private:
            void handleInputs(float timeDelta);
            void setPlayerState(PlayerState playerState);

            ggj::IInputManager<ggj::KeyboardKey> &m_inputManager;
            ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &m_animationManager;
            raylib::Vector2 m_velocity {0.f, 0.f};
            bool m_cameraShouldFollowPlayer {true};
            Animation m_animation;
            IMapper &m_mapper;
            PlayerState m_playerState{PlayerState::Idle};
            raylib::Vector2 m_startPos{};
    };

} // dev

#endif //GAME_DEV_TEMPLATE_PLAYER_H
