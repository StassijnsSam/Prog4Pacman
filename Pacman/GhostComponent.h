#pragma once

#include "BaseComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"
#include "RenderComponent.h"
#include "StateMachine.h"
#include "Observer.h"

class GhostComponent final : public dae::BaseComponent, public dae::Observer
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
	virtual void Recieve(int message) const override;

	void OnNotify(const dae::GameObject* actor, int event) override;

	int GetIsDead();

private:
	void OnCollision(dae::GameObject* other);

	bool m_IsDead{ false };
	void SetIsDead(bool isDead);

	void SetIsScared(bool isScared);

	//Work with a timer for now
	float m_DeadTimer{};
	float m_MaxDeadTime{ 3.0f };

	//State machine
	std::string m_NormalTexturePath{};
	dae::StateMachine* m_pStateMachine{};
};