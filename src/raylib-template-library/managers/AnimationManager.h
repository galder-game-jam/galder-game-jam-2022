//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_ANIMATIONMANAGER_H
#define GAME_DEV_TEMPLATE_ANIMATIONMANAGER_H

#include <map>
#include "../../gamedev-base/GameDevBase.h"
#include "../graphics/Animation.h"
#include "../enums/AnimationName.h"

namespace ggj
{

    class AnimationManager : public IAnimationManager<Animation, AnimationName>
    {
        public:
            Animation getAnimation(const AnimationName &id) override;

            bool initialize() override;

        private:
            std::map<AnimationName, Animation> m_animations;
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_ANIMATIONMANAGER_H
