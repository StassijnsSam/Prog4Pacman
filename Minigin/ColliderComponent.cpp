#include "ColliderComponent.h"

void dae::ColliderComponent::OnCollision(ColliderComponent* other)
{
	if (m_Callback) {
		auto otherGameObject = other->GetOwner();

		m_Callback(otherGameObject);
	}
}

dae::ColliderComponent::ColliderComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

void dae::ColliderComponent::Initialize()
{
}

void dae::ColliderComponent::Update()
{
}

void dae::ColliderComponent::Render() const
{
}

void dae::ColliderComponent::Recieve(int message) const
{
}
