#pragma once

#include "BaseComponent.h"

class WallComponent final: public dae::BaseComponent
{
public:
	WallComponent(dae::GameObject* pGameObject);
	virtual ~WallComponent() = default;

	WallComponent(const WallComponent& other) = delete;
	WallComponent(WallComponent&& other) = delete;
	WallComponent& operator=(const WallComponent& other) = delete;
	WallComponent& operator=(WallComponent&& other) = delete;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render()const override;
	virtual void Recieve(int message) const override;

private:
	void OnCollision(dae::GameObject* other);
};

