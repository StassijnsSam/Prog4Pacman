#pragma once

namespace dae {
	class GameObject;

	class BaseState
	{
	public:
		BaseState(GameObject* pGameObject);
		virtual ~BaseState() = default;

		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) = delete;

		virtual void Enter() = 0;
		virtual void Exit() = 0;
		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;

	protected:
		GameObject* m_pGameObject{};
	};
}


