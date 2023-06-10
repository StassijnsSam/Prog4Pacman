#include "ScoreDisplayComponent.h"
#include "Enums.h"
#include "PacmanComponent.h"

ScoreDisplayComponent::ScoreDisplayComponent(dae::GameObject* pGameObject)
	:BaseComponent(pGameObject)
{
}

void ScoreDisplayComponent::Initialize()
{
	m_pTextComponent = m_pOwner->GetComponent<dae::TextComponent>();
}

void ScoreDisplayComponent::Update()
{
}

void ScoreDisplayComponent::Render() const
{
}

void ScoreDisplayComponent::Recieve(int) const
{
}

void ScoreDisplayComponent::OnNotify(const dae::GameObject* pPlayer, int event)
{
	switch (event)
	{
	case EventType::PLAYER_GOT_SCORE:
	{
		auto pPlayerComponent = pPlayer->GetComponent<PacmanComponent>();
		if (pPlayerComponent) {
			SetScore(pPlayerComponent->GetScore());
		}
		break;
	}
	default:
		break;
	}
}

void ScoreDisplayComponent::SetScore(int score)
{
	m_Score = score;

	if (m_pTextComponent) {
		m_pTextComponent->SetText(std::to_string(score));
	}
}

void ScoreDisplayComponent::AddScore(int score)
{
	m_Score += score;
}
