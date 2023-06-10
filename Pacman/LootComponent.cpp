#include "LootComponent.h"
#include "CircleColliderComponent.h"
#include "PacmanComponent.h"

LootComponent::LootComponent(dae::GameObject* pGameObject, int pickupScore, bool makesInvincible)
	:BaseComponent(pGameObject), m_PickupScore(pickupScore), m_MakesInvincible(makesInvincible)
{
}

void LootComponent::Initialize()
{
	auto collider = GetOwner()->GetComponent<dae::CircleColliderComponent>();

	if (collider) {
		//Link the collision function
		collider->SetCollisionCallback([&](dae::GameObject* hit) { this->OnCollision(hit); });
	}
}

void LootComponent::Update()
{
}

void LootComponent::Render() const
{
}

void LootComponent::Recieve(int) const
{
}

int LootComponent::GetPickupScore()
{
	return m_PickupScore;
}

bool LootComponent::GetMakesInvincible()
{
	return m_MakesInvincible;
}

void LootComponent::OnCollision(dae::GameObject* other)
{
	//Check if you collided with a player, if so, destroy yourself
	auto playerComponent = other->GetComponent<PacmanComponent>();

	if (playerComponent) {
		m_pOwner->MarkForDeletion();
	}
}
