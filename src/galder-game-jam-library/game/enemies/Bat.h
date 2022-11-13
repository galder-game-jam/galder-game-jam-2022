//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_BAT_H
#define GAME_DEV_TEMPLATE_BAT_H

#include "../../graphics/PhysicsSprite.h"
#include "../../managers/AnimationManager.h"
#include "../../interfaces/system/IMapper.h"

namespace ggj
{

    class Bat : public PhysicsSprite
    {
        public:
            Bat() = default;
            Bat(ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &animationManager, IMapper &mapper, b2Body *body, const raylib::Vector2 &physicsSize,
            const raylib::Vector2 &spriteSize,
            const raylib::Rectangle &drawingRect, raylib::Texture * texture, const UserData &userData, const raylib::Vector2 &velocity, bool isVisible = true)
            : PhysicsSprite(body, physicsSize, spriteSize, drawingRect, texture, userData, isVisible), m_animationManager {animationManager}, m_mapper{mapper},
              m_velocity{velocity}
            {
                m_body->SetFixedRotation(true);
                m_animation = m_animationManager.getAnimation(AnimationName::EnemyBatMove);
                m_body->SetLinearVelocity({m_velocity.x, m_velocity.y});
                m_flip = m_velocity.x < 0.f;
//                m_body->SetGravityScale(0);
//                m_massData = {0.f, {0.f,0.f}, 0.f};
//                m_body->SetMassData(&m_massData);
            }
            void move(const raylib::Vector2 &toMove) override;

            void update(float timeDelta) override;

            void beginContact(PhysicsObject *a, PhysicsObject *b, b2Contact *contact) override;

        private:
            void turn();

            float m_turnTimer{0.f};
            float m_turnTriggerValue{3.f};
            ggj::IAnimationManager<ggj::Animation, ggj::AnimationName> &m_animationManager;
            IMapper &m_mapper;
            Animation m_animation;
            raylib::Vector2 m_velocity {0.f, 0.f};
//            b2MassData m_massData{};

    };

} // ggj

#endif //GAME_DEV_TEMPLATE_BAT_H
