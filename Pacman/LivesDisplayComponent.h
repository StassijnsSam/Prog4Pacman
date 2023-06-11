#pragma once
#include <string>

#include "BaseComponent.h"
#include "Observer.h"
#include "GameObject.h"
#include "RenderComponent.h"

class LivesDisplayComponent final : public dae::BaseComponent, public dae::Observer
{
public:
	LivesDisplayComponent(dae::GameObject* pGameObject, std::vector<dae::RenderComponent*>& pRenderComponents);

	~LivesDisplayComponent() override = default;
	LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
	LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
	LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
	LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

	void Initialize() override;
	void Update() override;
	void Render() const override;
	void Recieve(int message) const override;

	void OnNotify(const dae::GameObject* actor, int event) override;

	void SetLives(int lives);

private:
	int m_Lives{};

	std::vector<dae::RenderComponent*> m_pLivesIcons{};
};

