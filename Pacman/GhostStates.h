#pragma once

#include "BaseState.h"
#include "GameObject.h"
#include "RenderComponent.h"

class GhostNormalState final : public dae::BaseState
{
public:
	GhostNormalState(const std::string& normalTexture);
	virtual ~GhostNormalState() = default;

	GhostNormalState(const GhostNormalState& other) = delete;
	GhostNormalState(GhostNormalState&& other) = delete;
	GhostNormalState& operator=(const GhostNormalState& other) = delete;
	GhostNormalState& operator=(GhostNormalState&& other) = delete;

	virtual void Enter(dae::GameObject* pGameObject) override;
	virtual void Exit(dae::GameObject* pGameObject) override;

private:
	std::string m_NormalTexture{};
};

class GhostDeadState final : public dae::BaseState
{
public:
	GhostDeadState(const std::string& deadTexture);
	virtual ~GhostDeadState() = default;

	GhostDeadState(const GhostDeadState& other) = delete;
	GhostDeadState(GhostDeadState&& other) = delete;
	GhostDeadState& operator=(const GhostDeadState& other) = delete;
	GhostDeadState& operator=(GhostDeadState&& other) = delete;

	virtual void Enter(dae::GameObject* pGameObject) override;
	virtual void Exit(dae::GameObject* pGameObject) override;

private:
	std::string m_DeadTexture{};
};

