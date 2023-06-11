#pragma once

#include "BaseComponent.h"
#include "GameObject.h"
#include "Observer.h"
#include "Subject.h"
#include "RenderComponent.h"

class GhostComponent final : public dae::BaseComponent
{
public:
	GhostComponent(dae::GameObject* pGameObject, const std::string& deadTexturePath);
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

	//Render things
	dae::RenderComponent* m_pRenderComponent{};
	std::string m_NormalTexture{};
	std::string m_DeadTexture{};
};