//
// Created by robin on 05.11.22.
//

#include "CollisionManager.h"

namespace ggj
{
    void CollisionManager::BeginContact(b2Contact *contact)
    {
        b2Body *bodyA = contact->GetFixtureA()->GetBody();
        PhysicsObject *a = m_userDataManager.getUserData(bodyA);

        b2Body *bodyB = contact->GetFixtureB()->GetBody();
        PhysicsObject *b = m_userDataManager.getUserData(bodyB);
        
        if(a != nullptr && b != nullptr)
        {
            a->beginContact(a, b, contact);
            b->beginContact(b, a, contact);
            UserData* userDataA = a->getUserData();
            UserData* userDataB = b->getUserData();
            bodyA->ApplyLinearImpulseToCenter({userDataB->getForce().x, userDataB->getForce().y}, true);
            bodyB->ApplyLinearImpulseToCenter({userDataA->getForce().x, userDataA->getForce().y}, true);
            //bodyA->SetLinearVelocity({userDataB->getForce().x, userDataB->getForce().y});
            //bodyB->SetLinearVelocity({userDataA->getForce().x, userDataA->getForce().y});
        }
    }

    void CollisionManager::EndContact(b2Contact *contact)
    {
        b2Body *bodyA = contact->GetFixtureA()->GetBody();
        PhysicsObject *a = m_userDataManager.getUserData(bodyA);

        b2Body *bodyB = contact->GetFixtureB()->GetBody();
        PhysicsObject *b = m_userDataManager.getUserData(bodyB);

        if(a != nullptr && b != nullptr)
        {
            a->endContact(a, b, contact);
            b->endContact(b, a, contact);
        }
    }

    void CollisionManager::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
    {
        b2Body *bodyA = contact->GetFixtureA()->GetBody();
        PhysicsObject *a = m_userDataManager.getUserData(bodyA);

        b2Body *bodyB = contact->GetFixtureB()->GetBody();
        PhysicsObject *b = m_userDataManager.getUserData(bodyB);

        if(a != nullptr && b != nullptr)
        {
            a->preSolve(a, b, contact, oldManifold);
            b->preSolve(b, a, contact, oldManifold);
        }
    }

    void CollisionManager::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
    {
        b2Body *bodyA = contact->GetFixtureA()->GetBody();
        PhysicsObject *a = m_userDataManager.getUserData(bodyA);

        b2Body *bodyB = contact->GetFixtureB()->GetBody();
        PhysicsObject *b = m_userDataManager.getUserData(bodyB);

        if(a != nullptr && b != nullptr)
        {
            a->postSolve(a, b, contact, impulse);
            b->postSolve(b, a, contact, impulse);
        }
    }
} // dev