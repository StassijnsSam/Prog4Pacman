#include "ScoreComponent.h"
#include "Enums.h"

ScoreComponent::ScoreComponent(dae::GameObject* pGameObject)
	:BaseComponent(pGameObject)
{
}

void ScoreComponent::Initialize()
{
	m_pTextComponent = m_pOwner->GetComponent<dae::TextComponent>();
}

void ScoreComponent::Update()
{
}

void ScoreComponent::Render() const
{
}

void ScoreComponent::Recieve(int message) const
{
}

void ScoreComponent::Notify(const dae::GameObject* actor, int event)
{
	switch (event)
	{
	case EventType::PLAYER_GOT_SCORE:
		AddScore(10);
		break;
	default:
		break;
	}
}

void ScoreComponent::SetScore(int score)
{
	m_Score = score;
}

void ScoreComponent::AddScore(int score)
{
	m_Score += score;
}
