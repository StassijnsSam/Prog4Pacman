#include "CircleColliderComponent.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include <algorithm>

dae::CircleColliderComponent::CircleColliderComponent(GameObject* pOwner, float radius, bool isStatic, glm::vec2 offset)
	:ColliderComponent(pOwner, ColliderType::CIRCLE, isStatic), m_Radius(radius), m_Offset(offset)
{
}

bool dae::CircleColliderComponent::IsColliding(ColliderComponent* other)
{
	//If both colliders are static no need to check
	if (m_IsStatic && other->GetIsStatic()) {
		return false;
	}
	
	//Check if the other Collider is a circleCollider
	if (other->GetColliderType() == ColliderType::CIRCLE) {
		auto pOtherColliderCircle = dynamic_cast<CircleColliderComponent*>(other);

		auto ownerLocation = m_pOwner->GetTransform()->GetWorldPosition();
		auto otherOwnerLocation = pOtherColliderCircle->GetOwner()->GetTransform()->GetWorldPosition();

		//They collide if their distance is smaller than the sum of their collider radius
		return (glm::distance(ownerLocation, otherOwnerLocation) < m_Radius + pOtherColliderCircle->m_Radius);
	}

	

	if (other->GetColliderType() == ColliderType::BOX) {
		//Check if the other collider is a boxCollider
		auto pOtherColliderBox = dynamic_cast<BoxColliderComponent*>(other);

		auto ownerLocation = m_pOwner->GetTransform()->GetWorldPosition();
		auto otherOwnerLocation = pOtherColliderBox->GetOwner()->GetTransform()->GetWorldPosition();

		auto otherOwnerSize = pOtherColliderBox->GetSize();
		// Find the closest point to the circle within the rectangle
		float closestX = std::clamp(ownerLocation.x, otherOwnerLocation.x - otherOwnerSize.x / 2.0f, otherOwnerLocation.x + otherOwnerSize.x / 2.0f);
		float closestY = std::clamp(ownerLocation.y, otherOwnerLocation.y - otherOwnerSize.y / 2.0f, otherOwnerLocation.y + otherOwnerSize.y / 2.0f);

		//They collide if the distance from closest rectangle point to the circle origin is smaller than the radius
		return (glm::distance(ownerLocation, glm::vec2{closestX, closestY}) < m_Radius);
	}

	//Return false by default for now
	return false;
}

float dae::CircleColliderComponent::GetRadius()
{
	return m_Radius;
}
