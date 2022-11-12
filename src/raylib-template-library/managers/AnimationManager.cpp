//
// Created by soberga on 12.11.22.
//

#include "AnimationManager.h"

namespace ggj
{
    Animation AnimationManager::getAnimation(const AnimationName &id)
    {
        return (m_animations.count(id) > 0) ? m_animations[id] : Animation();
    }

    bool AnimationManager::initialize()
    {
        m_animations[AnimationName::None] =
        {
        raylib::Vector2(32, 32),
     {
                {raylib::Vector2(32 * 0,32), 100},
                {raylib::Vector2(32 * 1,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
                {raylib::Vector2(32 * 3,32), 100},
                {raylib::Vector2(32 * 4,32), 100},
                {raylib::Vector2(32 * 5,32), 100},
                {raylib::Vector2(32 * 6,32), 100},
                {raylib::Vector2(32 * 7,32), 100},
                {raylib::Vector2(32 * 8,32), 100},
                {raylib::Vector2(32 * 9,32), 100},
                {raylib::Vector2(32 * 10,32), 100},
                {raylib::Vector2(32 * 11,32), 100},
                {raylib::Vector2(32 * 12,32), 100},
                {raylib::Vector2(32 * 13,32), 100},
                {raylib::Vector2(32 * 14,32), 100},
                {raylib::Vector2(32 * 15,32), 100},
                {raylib::Vector2(32 * 16,32), 100},
                {raylib::Vector2(32 * 17,32), 100},
                {raylib::Vector2(32 * 18,32), 100},
             }
        };
        m_animations[AnimationName::PlayerIdle] =
        {
        raylib::Vector2(32, 32),
    {
                {raylib::Vector2(32 * 0,32), 100},
            }
        };
        m_animations[AnimationName::PlayerWalk] =
        {
        raylib::Vector2(32, 32),
    {
                {raylib::Vector2(32 * 1,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
                {raylib::Vector2(32 * 3,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
            }
        };
        m_animations[AnimationName::PlayerJump] =
        {
        raylib::Vector2(32, 32),
      {
                {raylib::Vector2(32 * 5,32), 100},
              }
        };
        m_animations[AnimationName::PlayerFall] =
        {
        raylib::Vector2(32, 32),
     {
                {raylib::Vector2(32 * 6,32), 100},
             }
        };
        m_animations[AnimationName::EnemyBatMove] =
        {
        raylib::Vector2(32, 32),
     {
                {raylib::Vector2(32 * 1,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
                {raylib::Vector2(32 * 3,32), 100},
                {raylib::Vector2(32 * 2,32), 100},
             }
        };
        m_animations[AnimationName::EnemyBatDead] =
        {
        raylib::Vector2(32, 32),
     {
                {raylib::Vector2(32 * 0,32), 100},
             }
        };
        return true;
    }
} // ggj