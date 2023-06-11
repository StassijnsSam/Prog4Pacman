#include "GhostStates.h"

#include "GhostComponent.h"

GhostNormalState::GhostNormalState(dae::GameObject* pGameObject, const std::string& normalTexture):
	BaseState(pGameObject), m_NormalTexture(normalTexture)
{
}

void GhostNormalState::Enter()
{
	//Check if this is on a ghost
	auto ghostComponent = m_pGameObject->GetComponent<GhostComponent>();

	if (!ghostComponent) {
		return;
	}

	//Check if it has a renderComponent
	auto renderComponent = m_pGameObject->GetComponent<dae::RenderComponent>();

	if (renderComponent) {
		renderComponent->SetTexture(m_NormalTexture);
	}
}

void GhostNormalState::Exit()
{
}

void GhostNormalState::Update()
{
}

void GhostNormalState::FixedUpdate()
{
}

GhostDeadState::GhostDeadState(dae::GameObject* pGameObject, const std::string& deadTexture):
	BaseState(pGameObject), m_DeadTexture(deadTexture)
{
}

void GhostDeadState::Enter()
{
	//Check if this is on a ghost
	auto ghostComponent = m_pGameObject->GetComponent<GhostComponent>();

	if (!ghostComponent) {
		return;
	}

	//Check if it has a renderComponent
	auto renderComponent = m_pGameObject->GetComponent<dae::RenderComponent>();

	if (renderComponent) {
		renderComponent->SetTexture(m_DeadTexture);
	}
}

void GhostDeadState::Exit()
{
}

void GhostDeadState::Update()
{
}

void GhostDeadState::FixedUpdate()
{
}
