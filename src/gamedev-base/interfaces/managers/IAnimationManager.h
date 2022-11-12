//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_IANIMATIONMANAGER_H
#define GAME_DEV_TEMPLATE_IANIMATIONMANAGER_H

#include <string>

namespace ggj
{
    template<class TAnimation, class TId>
    class IAnimationManager
    {
        public:
            virtual ~IAnimationManager() noexcept = default;
            virtual TAnimation getAnimation(const TId &id) = 0;
            virtual bool initialize() = 0;
    };
} // ggj

#endif //GAME_DEV_TEMPLATE_IANIMATIONMANAGER_H
