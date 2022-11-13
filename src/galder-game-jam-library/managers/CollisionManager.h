//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_COLLISIONMANAGER_H
#define GAME_DEV_TEMPLATE_COLLISIONMANAGER_H

#include "box2d/box2d.h"
#include "../interfaces/manager/IUserDataManager.h"
#include "../system/UserData.hpp"
#include "../graphics/PhysicsObject.h"

namespace ggj
{

    class CollisionManager : public b2ContactListener
    {
        public:
            explicit CollisionManager(IUserDataManager<PhysicsObject*> &userDataManager) : m_userDataManager{userDataManager}
            {
            }

            //Overridden stuff from Box2D
            void BeginContact(b2Contact *contact) override;
            void EndContact(b2Contact *contact) override;
            void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
            void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;

        private:
            IUserDataManager<PhysicsObject*> &m_userDataManager;
    };

} // dev

#endif //GAME_DEV_TEMPLATE_COLLISIONMANAGER_H
