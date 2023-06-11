#include "LivesDisplayComponent.h"
#include "Enums.h"
#include "PacmanComponent.h"

LivesDisplayComponent::LivesDisplayComponent(dae::GameObject* pGameObject, std::vector<dae::RenderComponent*>& pRenderComponents):
	BaseComponent(pGameObject), m_pLivesIcons(pRenderComponents)
{
	m_Lives = static_cast<int>(m_pLivesIcons.size());
}

void LivesDisplayComponent::Initialize()
{
}

void LivesDisplayComponent::Update()
{
}

void LivesDisplayComponent::Render() const
{
}

void LivesDisplayComponent::Recieve(int) const
{
}

void LivesDisplayComponent::OnNotify(const dae::GameObject* pPlayer, int event)
{
	switch (event)
	{
	case EventType::PLAYER_HURT:
	{
		auto pPlayerComponent = pPlayer->GetComponent<PacmanComponent>();
		if (pPlayerComponent) {
			SetLives(pPlayerComponent->GetLives());
		}
		break;
	}
	default:
		break;
	}
}

void LivesDisplayComponent::SetLives(int lives)
{
	m_Lives = lives;

	for (int i{ 0 }; i < static_cast<int>(m_pLivesIcons.size()); ++i) {
		auto pLifeIcon = m_pLivesIcons.at(i);

		if (m_Lives > i + 1) {
			pLifeIcon->SetIsVisible(false);
		}
		else {
			//In case you could regain lives
			pLifeIcon->SetIsVisible(true);
		}
	}
}
