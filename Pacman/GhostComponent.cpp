#include "GhostComponent.h"
#include "PacmanComponent.h"
#include "CircleColliderComponent.h"
#include "Timetracker.h"
#include "GhostStates.h"
#include "Enums.h"

GhostComponent::GhostComponent(dae::GameObject* pGameObject)
	:BaseComponent(pGameObject)
{
}

void GhostComponent::Initialize()
{
	auto collider = GetOwner()->GetComponent<dae::CircleColliderComponent>();

	if (collider) {
		//Link the collision function
		collider->SetCollisionCallback([&](dae::GameObject* hit) { this->OnCollision(hit); });
	}

	auto stateMachine = GetOwner()->GetComponent<dae::StateMachine>();

	if (stateMachine) {
		m_pStateMachine = stateMachine;
	}

	//Grab normal texture from renderComponent
	auto renderComponent = GetOwner()->GetComponent<dae::RenderComponent>();

	if (renderComponent) {
		m_NormalTexturePath = renderComponent->GetTexturePath();
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

void GhostComponent::OnNotify(const dae::GameObject*, int event)
{
	switch (event)
	{
	case EventType::PLAYER_CAN_KILL:
	{
		SetIsScared(true);
		break;
	}
	case EventType::PLAYER_CAN_NOT_KILL:
	{
		SetIsScared(false);
		break;
	}
	default:
		break;
	}
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

	if (isDead) {
		m_DeadTimer = m_MaxDeadTime;
	}
}

void GhostComponent::SetIsScared(bool isScared)
{
	//Change texture
	if (isScared) {
		if (m_pStateMachine) {
			m_pStateMachine->UpdateState(std::make_unique<GhostDeadState>(GetOwner(), "scaredGhost.png"));
		}
	}
	else
	{
		if (m_pStateMachine) {
			m_pStateMachine->UpdateState(std::make_unique<GhostNormalState>(GetOwner(), m_NormalTexturePath));
		}
	}
}
