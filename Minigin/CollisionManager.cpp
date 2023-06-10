#include "CollisionManager.h"

void dae::CollisionManager::Add(ColliderComponent* colliderComponent)
{
    //Check if the collider is already in there
    auto it = std::find(m_pColliders.begin(), m_pColliders.end(), colliderComponent);

    if (it != m_pColliders.end()) {
        return;
    }

    m_pColliders.emplace_back(colliderComponent);
}

void dae::CollisionManager::Remove(ColliderComponent* colliderComponent)
{
    //Check if the collider is in there
    auto it = std::find(m_pColliders.begin(), m_pColliders.end(), colliderComponent);

    if (it == m_pColliders.end()) {
        //Collider not found
        return;
    }

    m_pColliders.erase(it);
}

void dae::CollisionManager::FixedUpdate()
{
    //Double loop over all colliders
    for (auto pCollider : m_pColliders) {
        for (auto pOtherCollider : m_pColliders) {
            if (pCollider == pOtherCollider) {
                //Make sure to not self trigger
                continue;
            }

            //If they are colliding trigger the callbacks on both colliders
            if (pCollider->IsColliding(pOtherCollider)) {
                pCollider->OnCollision(pOtherCollider);
            }
        }
    }
}

