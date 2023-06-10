#pragma once

#include "BaseComponent.h"
#include "GameObject.h"

class LootComponent final : public dae::BaseComponent
{
public:
	LootComponent(dae::GameObject* pGameObject, int pickupScore, bool makesInvincible = false);
	virtual ~LootComponent() = default;

	LootComponent(const LootComponent& other) = delete;
	LootComponent(LootComponent&& other) = delete;
	LootComponent& operator=(const LootComponent& other) = delete;
	LootComponent& operator=(LootComponent&& other) = delete;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render()const override;
	void Recieve(int message) const override;

	int GetPickupScore();
	bool GetMakesInvincible();

private:
	void OnCollision(dae::GameObject* other);
	
	int m_PickupScore{};
	bool m_MakesInvincible{ false };
};

