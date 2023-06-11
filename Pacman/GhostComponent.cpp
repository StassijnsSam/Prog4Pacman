#include "GhostComponent.h"
#include "PacmanComponent.h"
#include "CircleColliderComponent.h"
#include "Timetracker.h"

GhostComponent::GhostComponent(dae::GameObject* pGameObject, const std::string& deadTexturePath)
	:BaseComponent(pGameObject), m_DeadTexture(deadTexturePath)
{
}

void GhostComponent::Initialize()
{
	auto collider = GetOwner()->GetComponent<dae::CircleColliderComponent>();

	if (collider) {
		//Link the collision function
		collider->SetCollisionCallback([&](dae::GameObject* hit) { this->OnCollision(hit); });
	}

	auto renderComponent = GetOwner()->GetComponent<dae::RenderComponent>();

	if (renderComponent) {
		m_pRenderComponent = renderComponent;

		m_NormalTexture = m_pRenderComponent->GetTexturePath();
	}
}

void GhostComponent::Update()
{
	//Move towards pacman / or away if dead

	//Update death timer
	const float deltaTime = Time::GetInstance().GetDeltaTime();

	if (m_IsDead) {
		m_DeadTimer -= deltaTime;

		if (m_DeadTimer <= 0.f) {
			SetIsDead(false);
		}
	}
}

void GhostComponent::Render() const
{
}

void GhostComponent::Recieve(int) const
{
}

int GhostComponent::GetIsDead()
{
	return m_IsDead;
}

void GhostComponent::OnCollision(dae::GameObject* other)
{
	//Check if you collided with a player, if so, destroy yourself
	auto playerComponent = other->GetComponent<PacmanComponent>();

	if (playerComponent) {
		//Check if you are dead
		if (m_IsDead) {
			return;
		}

		//Check if the player can kill
		if (playerComponent->GetCanKill()) {
			SetIsDead(true);
		}
		
		//Otherwise do nothing (player handles losing a life)
	}
}

void GhostComponent::SetIsDead(bool isDead)
{
	m_IsDead = isDead;

	//Change texture
	if (m_IsDead) {
		if (m_pRenderComponent) {
			m_pRenderComponent->SetTexture(m_DeadTexture);
		}
	}
	else
	{
		if (m_pRenderComponent) {
			m_pRenderComponent->SetTexture(m_NormalTexture);
		}
	}

	//Set max dead timer
	if (isDead) {
		m_DeadTimer = m_MaxDeadTime;
	}
}
