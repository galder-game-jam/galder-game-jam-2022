//
// Created by robin on 05.11.22.
//

#ifndef GAME_DEV_TEMPLATE_COLLISIONMANAGER_H
#define GAME_DEV_TEMPLATE_COLLISIONMANAGER_H

#include "box2d/box2d.h"

namespace dev
{

    class CollisionManager : public b2ContactListener
    {
        public:
            CollisionManager() = default;

            //Overridden stuff from Box2D
            void BeginContact(b2Contact *contact) override;
            void EndContact(b2Contact *contact) override;
            void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
            void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;
    };

} // dev

#endif //GAME_DEV_TEMPLATE_COLLISIONMANAGER_H
