#pragma once

#include "BaseComponent.h"
#include <memory>
#include "BaseState.h"

namespace dae {
	class StateMachine final : public BaseComponent
	{
	public:
		StateMachine(GameObject* pOwner, std::unique_ptr<BaseState>&& startState);
		~StateMachine() override = default;

		StateMachine(const StateMachine& other) = delete;
		StateMachine(StateMachine&& other) = delete;
		StateMachine& operator=(const StateMachine& other) = delete;
		StateMachine& operator=(StateMachine&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message) const override;
		virtual void FixedUpdate() override;

		void UpdateState(std::unique_ptr<BaseState>&& state);

	private:
		std::unique_ptr<BaseState> m_pCurrentState{};
	};
}