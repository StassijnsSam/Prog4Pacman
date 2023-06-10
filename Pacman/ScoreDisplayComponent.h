#pragma once
#include <string>

#include "BaseComponent.h"
#include "Observer.h"
#include "GameObject.h"
#include "TextComponent.h"

class ScoreDisplayComponent final : public dae::BaseComponent, public dae::Observer
{
public:
	ScoreDisplayComponent(dae::GameObject* pGameObject);

	~ScoreDisplayComponent() override = default;
	ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
	ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
	ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

	void Initialize() override;
	void Update() override;
	void Render() const override;
	void Recieve(int message) const override;

	void OnNotify(const dae::GameObject* actor, int event) override;
	
	void SetScore(int score);
	void AddScore(int score);

private:
	int m_Score{};

	dae::TextComponent* m_pTextComponent{};
};

