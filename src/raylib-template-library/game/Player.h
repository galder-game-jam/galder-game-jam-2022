//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_PLAYER_H
#define GAME_DEV_TEMPLATE_PLAYER_H

#include "../graphics/PhysicsSprite.h"
#include "../enums/KeyboardKey.h"
#include "../managers/AnimationManager.h"

namespace ggj
{
    class Player : public PhysicsSprite
    {
        public:
            Player() = default;
            Player(ggj::IInputManager<ggj::KeyboardKey> &inputManager, ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animationManager, b2Body *body, const raylib::Vector2 &physicsSize,
                   const raylib::Vector2 &spriteSize,
                   const raylib::Rectangle &drawingRect, raylib::Texture * texture, bool isVisible = true)
            : PhysicsSprite(body, physicsSize, spriteSize, drawingRect, texture, isVisible), m_inputManager {inputManager}, m_animationManager {animationManager}
            {
                m_body->SetFixedRotation(true);
                m_animation = m_animationManager.getAnimation(AnimationName::None);
            }

            [[nodiscard]] const Vector2 &getVelocity() const;
            [[nodiscard]] bool cameraShouldFollowPlayer() const;

            void update(float timeDelta) override;
            void draw() override;

        private:
            void handleInputs(float timeDelta);

            ggj::IInputManager<ggj::KeyboardKey> &m_inputManager;
            ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &m_animationManager;
            Vector2 m_velocity {0.f, 0.f};
            bool m_cameraShouldFollowPlayer {false};
            Animation m_animation;
    };

} // dev

#endif //GAME_DEV_TEMPLATE_PLAYER_H
