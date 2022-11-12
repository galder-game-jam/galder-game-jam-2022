//
// Created by robin on 05.11.22.
//

#include "CollisionManager.h"

namespace ggj
{
    void CollisionManager::BeginContact(b2Contact *contact)
    {
        b2Body *bodyA = contact->GetFixtureA()->GetBody();
        UserData *a = m_userDataManager.getUserData(bodyA);

        b2Body *bodyB = contact->GetFixtureB()->GetBody();
        UserData *b = m_userDataManager.getUserData(bodyB);
        
        if(a != nullptr && b != nullptr)
        {
            bodyA->SetLinearVelocity({b->getForce().x, b->getForce().y});
            bodyB->SetLinearVelocity({a->getForce().x, a->getForce().y});
        }
    }

    void CollisionManager::EndContact(b2Contact *contact)
    {

    }

    void CollisionManager::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
    {
    }

    void CollisionManager::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
    {

    }
} // dev