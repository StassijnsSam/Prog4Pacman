#pragma once

#include "BaseComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"

class PacmanComponent final : public dae::BaseComponent
{
public:
	PacmanComponent(dae::GameObject* pGameObject);
	virtual ~PacmanComponent() = default;

	PacmanComponent(const PacmanComponent& other) = delete;
	PacmanComponent(PacmanComponent&& other) = delete;
	PacmanComponent& operator=(const PacmanComponent& other) = delete;
	PacmanComponent& operator=(PacmanComponent&& other) = delete;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render()const override;
	void Recieve(int message) const override;

	void AddObserver(dae::Observer* observer);

	int GetScore();
	int GetLives();

	bool GetCanKill();
	bool GetIsInvincible();

private:
	void OnCollision(dae::GameObject* other);

	int m_Lives{ 3 };
	int m_Score{ 0 };

	bool m_CanKill{ false };

	void EnableCanKill();
	float m_CanKillTimer{};
	float m_MaxCanKillTime{ 5.0f };

	bool m_IsInvincible{ false };

	void EnableInvincible();
	float m_InvincibilityTimer{};
	float m_MaxInvincibilityTime{ 2.0f };

	std::unique_ptr<dae::Subject> m_PacmanSubject{};
};

