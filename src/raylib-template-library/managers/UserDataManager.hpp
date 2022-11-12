//
// Created by soberga on 12.11.22.
//

#ifndef GAME_DEV_TEMPLATE_USERDATAMANAGER_HPP
#define GAME_DEV_TEMPLATE_USERDATAMANAGER_HPP

#include <map>
#include "../interfaces/manager/IUserDataManager.h"
#include "../system/UserData.hpp"

namespace ggj
{
    class UserDataManager : public IUserDataManager<PhysicsObject*>
    {
        public:
            PhysicsObject *getUserData(b2Body *body) override
            {
                return (m_userData.count(body) > 0) ? m_userData[body] : nullptr;
            }

            void addUserData(b2Body *body, PhysicsObject *userData) override
            {
                m_userData[body] = userData;
            }

        private:
            std::map<b2Body*, PhysicsObject*> m_userData;
    };
}

#endif //GAME_DEV_TEMPLATE_USERDATAMANAGER_HPP
