#include "CircleColliderComponent.h"

dae::CircleColliderComponent::CircleColliderComponent(GameObject* pOwner, float radius, glm::vec2 offset)
	:ColliderComponent(pOwner), m_Radius(radius), m_Offset(offset)
{
}
