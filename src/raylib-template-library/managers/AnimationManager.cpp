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
                        {raylib::Vector2(32 * 0,0), 500},
                        {raylib::Vector2(32 * 1,0), 500},
                        {raylib::Vector2(32 * 2,0), 500},
                        {raylib::Vector2(32 * 3,0), 500},
                        {raylib::Vector2(32 * 4,0), 500},
                        {raylib::Vector2(32 * 5,0), 500},
                        {raylib::Vector2(32 * 6,0), 500},
                        {raylib::Vector2(32 * 7,0), 500},
                        {raylib::Vector2(32 * 8,0), 500},
                        {raylib::Vector2(32 * 9,0), 500},
                        {raylib::Vector2(32 * 10,0), 500},
                        {raylib::Vector2(32 * 11,0), 500},
                        {raylib::Vector2(32 * 12,0), 500},
                        {raylib::Vector2(32 * 13,0), 500},
                        {raylib::Vector2(32 * 14,0), 500},
                        {raylib::Vector2(32 * 15,0), 500},
                        {raylib::Vector2(32 * 16,0), 500},
                        {raylib::Vector2(32 * 17,0), 500},
                        {raylib::Vector2(32 * 18,0), 500},
                     }
                };
        return true;
    }
} // ggj