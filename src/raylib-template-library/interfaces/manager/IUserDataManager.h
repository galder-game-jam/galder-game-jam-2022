//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_IUSERDATAMANAGER_H
#define GAME_DEV_TEMPLATE_IUSERDATAMANAGER_H

#include "box2d/box2d.h"

namespace ggj
{

    template<class T>
    class IUserDataManager
    {

        public:
            virtual ~IUserDataManager() noexcept = default;
            virtual T* getUserData(b2Body *body) = 0;
            virtual void addUserData(b2Body *body, const T &userData) = 0;
    };

} // ggj

#endif //GAME_DEV_TEMPLATE_IUSERDATAMANAGER_H
