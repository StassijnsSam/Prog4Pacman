#include "ColliderComponent.h"
#include "CollisionManager.h"

void dae::ColliderComponent::OnCollision(ColliderComponent* other)
{
	if (m_Callback) {
		auto otherGameObject = other->GetOwner();

		m_Callback(otherGameObject);
	}
}

void dae::ColliderComponent::SetCollisionCallback(std::function<void(GameObject* other)> callback)
{
	m_Callback = callback;
}

dae::ColliderComponent::ColliderType dae::ColliderComponent::GetColliderType()
{
	return m_ColliderType;
}

bool dae::ColliderComponent::GetIsStatic()
{
	return m_IsStatic;
}

dae::ColliderComponent::ColliderComponent(GameObject* pOwner, ColliderType colliderType, bool isStatic)
	:BaseComponent(pOwner), m_ColliderType(colliderType), m_IsStatic(isStatic)
{
	CollisionManager::GetInstance().Add(this);
}

dae::ColliderComponent::~ColliderComponent()
{
	CollisionManager::GetInstance().Remove(this);
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

void dae::ColliderComponent::Recieve(int) const
{
}
