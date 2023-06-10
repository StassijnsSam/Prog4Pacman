#pragma once
#include <string>

#include "BaseComponent.h"
#include "Observer.h"
#include "GameObject.h"
#include "TextComponent.h"

class ScoreComponent final : public dae::BaseComponent, public dae::Observer
{
public:
	ScoreComponent(dae::GameObject* pGameObject);

	~ScoreComponent() override = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) = delete;

	void Initialize() override;
	void Update() override;
	void Render() const override;
	void Recieve(int message) const override;

	void Notify(const dae::GameObject* actor, int event) override;
	
	void SetScore(int score);
	void AddScore(int score);

private:
	int m_Score{};
	std::string m_ScoreText{};

	dae::TextComponent* m_pTextComponent{};
};

