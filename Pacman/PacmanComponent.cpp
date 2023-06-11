#include "PacmanComponent.h"
#include "CircleColliderComponent.h"
#include "LootComponent.h"
#include "Timetracker.h"
#include "GhostComponent.h"
#include "Enums.h"

PacmanComponent::PacmanComponent(dae::GameObject* pGameObject)
	:BaseComponent(pGameObject)
{
	m_PacmanSubject = std::make_unique<dae::Subject>();
}

void PacmanComponent::Initialize()
{
	auto collider = GetOwner()->GetComponent<dae::CircleColliderComponent>();

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

	if (m_CanKill) {
		m_CanKillTimer -= deltaTime;

		if (m_CanKillTimer <= 0.f) {
			m_CanKill = false;
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
	if (observer) {
		m_PacmanSubject.get()->AddObserver(observer);
	}
}

int PacmanComponent::GetScore()
{
	return m_Score;
}

int PacmanComponent::GetLives()
{
	return m_Lives;
}

bool PacmanComponent::GetCanKill()
{
	return m_CanKill;
}

bool PacmanComponent::GetIsInvincible()
{
	return m_IsInvincible;
}

void PacmanComponent::OnCollision(dae::GameObject* other)
{
	//Check if its an enemy
	auto ghostComponent = other->GetComponent<GhostComponent>();
	if (ghostComponent) {
		if (m_CanKill) {
			//gain some score?
			
		}

		if (!m_IsInvincible && !m_CanKill) {
			//Lose a life
			m_Lives -= 1;

			//Temporary invincibility
			EnableInvincible();

			//Notify lives observer
			m_PacmanSubject.get()->Notify(this->GetOwner(), EventType::PLAYER_HURT);
		}
	}

	//Check if its loot
	auto lootComponent = other->GetComponent<LootComponent>();
	if (lootComponent) {
		//Check the score
		int score = lootComponent->GetPickupScore();
		bool makesInvincible = lootComponent->GetMakesInvincible();

		if (makesInvincible) {
			//Can kill ghosts
			EnableCanKill();
		}

		m_Score += score;

		//Notify score observer
		m_PacmanSubject.get()->Notify(this->GetOwner(), EventType::PLAYER_GOT_SCORE);
	}
}

void PacmanComponent::EnableCanKill()
{
	m_CanKill = true;

	m_CanKillTimer = m_MaxCanKillTime;
}

void PacmanComponent::EnableInvincible()
{
	m_IsInvincible = true;

	m_InvincibilityTimer = m_MaxInvincibilityTime;
}
