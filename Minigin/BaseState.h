#pragma once

namespace dae {
	class GameObject;

	class BaseState
	{
		BaseState() = default;
		virtual ~BaseState() = default;

		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) = delete;

		virtual void Enter(GameObject* pGameObject) = 0;
		virtual void Exit(GameObject* pGameObject) = 0;
	};
}


