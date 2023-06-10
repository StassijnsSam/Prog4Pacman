#include "PacmanComponent.h"
#include "ColliderComponent.h"
#include "LootComponent.h"
#include "Timetracker.h"

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
	const float deltaTime = Time::GetInstance().GetDeltaTime();

	if (m_IsInvincible) {
		m_InvincibilityTimer -= deltaTime;

		if (m_InvincibilityTimer <= 0.f) {
			m_IsInvincible = false;
		}
	}
}

void PacmanComponent::Render() const
{
}

void PacmanComponent::Recieve(int) const
{
}

void PacmanComponent::AddObserver(dae::Observer* observer)
{
	m_PacmanSubject->AddObserver(observer);
}

void PacmanComponent::OnCollision(dae::GameObject* other)
{
	//Check if its an enemy

	//Check if its loot
	auto lootComponent = other->GetComponent<LootComponent>();
	if (lootComponent) {
		//Check the score
		int score = lootComponent->GetPickupScore();
		bool makesInvincible = lootComponent->GetMakesInvincible();

		if (makesInvincible) {
			EnableInvincible();
		}

		m_Score += score;

		//Notify score observer
	}
}

void PacmanComponent::EnableInvincible()
{
	m_IsInvincible = true;

	m_InvincibilityTimer = m_MaxInvincibilityTime;
}
