#pragma once
#include "Command.h"
#include "glm/vec2.hpp"

namespace dae {

	class Move final : public Command
	{
	public:
		Move(GameObject* pGameObject, const glm::vec2& dir, float moveSpeed);
		virtual void Execute() override;

	private:
		GameObject* m_pGameObject{};
		glm::vec2 m_Direction{};
		float m_MoveSpeed{};
	};
}

