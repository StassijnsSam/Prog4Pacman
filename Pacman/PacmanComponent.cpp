#include "PacmanComponent.h"
#include "ColliderComponent.h"

PacmanComponent::PacmanComponent(dae::GameObject* pGameObject)
	:BaseComponent(pGameObject)
{
	m_PacmanSubject = std::make_unique<dae::Subject>();
}

void PacmanComponent::Initialize()
{
	auto collider = GetOwner()->GetComponent<dae::ColliderComponent>();

	if (collider) {
		//Link the collision function
		collider->SetCollisionCallback([&](dae::GameObject* hit) { this->OnCollision(hit); });
	}
}

void PacmanComponent::Update()
{
}

void PacmanComponent::Render() const
{
}

void PacmanComponent::Recieve(int) const
{
}

void PacmanComponent::OnCollision(dae::GameObject* other)
{
	//Check if its an enemy

	//Check if its loot
	//	Check if its a pellet
	//	Check if its a cherry
}
