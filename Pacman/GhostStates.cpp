#include "GhostStates.h"

#include "GhostComponent.h"

GhostNormalState::GhostNormalState(const std::string& normalTexture):
	m_NormalTexture(normalTexture)
{
}

void GhostNormalState::Enter(dae::GameObject* pGameObject)
{
	//Check if this is on a ghost
	auto ghostComponent = pGameObject->GetComponent<GhostComponent>();

	if (!ghostComponent) {
		return;
	}

	//Check if it has a renderComponent
	auto renderComponent = pGameObject->GetComponent<dae::RenderComponent>();

	if (renderComponent) {
		renderComponent->SetTexture(m_NormalTexture);
	}
}

void GhostNormalState::Exit(dae::GameObject*)
{
}

GhostDeadState::GhostDeadState(const std::string& deadTexture):
	m_DeadTexture(deadTexture)
{
}

void GhostDeadState::Enter(dae::GameObject* pGameObject)
{
	//Check if this is on a ghost
	auto ghostComponent = pGameObject->GetComponent<GhostComponent>();

	if (!ghostComponent) {
		return;
	}

	//Check if it has a renderComponent
	auto renderComponent = pGameObject->GetComponent<dae::RenderComponent>();

	if (renderComponent) {
		renderComponent->SetTexture(m_DeadTexture);
	}
}

void GhostDeadState::Exit(dae::GameObject* pGameObject)
{
}
