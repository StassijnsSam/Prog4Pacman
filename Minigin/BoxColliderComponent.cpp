#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "GameObject.h"
#include <algorithm>

dae::BoxColliderComponent::BoxColliderComponent(GameObject* pOwner, glm::vec2 size, glm::vec2 offset):
	ColliderComponent(pOwner), m_Size(size), m_Offset(offset)
{
}

bool dae::BoxColliderComponent::IsColliding(ColliderComponent* other)
{
	//Check if the other Collider is a circleCollider
	auto pOtherColliderCircle = dynamic_cast<CircleColliderComponent*>(other);

	if (pOtherColliderCircle) {
		auto ownerLocation = m_pOwner->GetTransform()->GetWorldPosition();
		auto otherOwnerLocation = pOtherColliderCircle->GetOwner()->GetTransform()->GetWorldPosition();
		
		float otherOwnerRadius = pOtherColliderCircle->GetRadius();
		// Find the closest point to the circle within the rectangle
		float closestX = std::clamp(otherOwnerLocation.x, ownerLocation.x - m_Size.x / 2.0f, ownerLocation.x + m_Size.x / 2.0f);
		float closestY = std::clamp(otherOwnerLocation.y, ownerLocation.y - m_Size.y / 2.0f, ownerLocation.y + m_Size.y / 2.0f);

		//They collide if the distance from closest rectangle point to the circle origin is smaller than the radius
		return (glm::distance(ownerLocation, glm::vec2{ closestX, closestY }) < otherOwnerRadius);
	}

	//Check if the other Collider is a boxCollider
	auto pOtherColliderBox = dynamic_cast<BoxColliderComponent*>(other);

	if (pOtherColliderBox) {
		auto ownerLocation = m_pOwner->GetTransform()->GetWorldPosition();
		auto otherOwnerLocation = pOtherColliderBox->GetOwner()->GetTransform()->GetWorldPosition();

		glm::vec2 otherColliderSize = pOtherColliderBox->GetSize();

		// Calculate the half widths and half heights of the boxes
		float halfWidth1 = m_Size.x / 2.0f;
		float halfHeight1 = m_Size.y / 2.0f;
		float halfWidth2 = otherColliderSize.x / 2.0f;
		float halfHeight2 = otherColliderSize.y / 2.0f;

		// Calculate the distance between the centers of the two boxes
		float distanceX = std::abs(otherOwnerLocation.x - ownerLocation.x);
		float distanceY = std::abs(otherOwnerLocation.y - ownerLocation.y);

		// Check for collision by comparing the distances with the half widths and half heights
		if (distanceX <= halfWidth1 + halfWidth2 && distanceY <= halfHeight1 + halfHeight2) {
			return true;  // Collision detected
		}

		return false;  // No collision
	}

	//return false by default for now
	return false;
}

const glm::vec2& dae::BoxColliderComponent::GetSize()
{
	return m_Size;
}
