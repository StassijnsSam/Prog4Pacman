#include "CircleColliderComponent.h"
#include "GameObject.h"

dae::CircleColliderComponent::CircleColliderComponent(GameObject* pOwner, float radius, glm::vec2 offset)
	:ColliderComponent(pOwner), m_Radius(radius), m_Offset(offset)
{
}

bool dae::CircleColliderComponent::IsColliding(ColliderComponent* other)
{
	//Check if the other Collider is a circleCollider
	auto pOtherCollider = dynamic_cast<CircleColliderComponent*>(other);

	if (pOtherCollider) {

		auto ownerLocation = m_pOwner->GetTransform()->GetWorldPosition();
		auto otherOwnerLocation = pOtherCollider->GetOwner()->GetTransform()->GetWorldPosition();

		//They collide if their distance is smaller than the sum of their collider radius
		return (glm::distance(ownerLocation, otherOwnerLocation) < m_Radius + pOtherCollider->m_Radius);
	}

	//Possible to add other collider types (like box, and then have the other implementations here)

	//Return false by default for now
	return false;
}
