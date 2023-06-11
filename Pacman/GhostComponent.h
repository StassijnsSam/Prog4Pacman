#pragma once

#include "BaseComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"
#include "RenderComponent.h"
#include "StateMachine.h"

class GhostComponent final : public dae::BaseComponent
{
public:
	GhostComponent(dae::GameObject* pGameObject);
	virtual ~GhostComponent() = default;

	GhostComponent(const GhostComponent& other) = delete;
	GhostComponent(GhostComponent&& other) = delete;
	GhostComponent& operator=(const GhostComponent& other) = delete;
	GhostComponent& operator=(GhostComponent&& other) = delete;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render()const override;
	void Recieve(int message) const override;

	int GetIsDead();

private:
	void OnCollision(dae::GameObject* other);

	bool m_IsDead{ false };
	void SetIsDead(bool isDead);

	//Work with a timer for now
	float m_DeadTimer{};
	float m_MaxDeadTime{ 3.0f };

	//State machine
	std::string m_NormalTexturePath{};
	dae::StateMachine* m_pStateMachine{};
};