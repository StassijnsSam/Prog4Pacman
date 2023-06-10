#pragma once

#include "ColliderComponent.h"
#include "glm/vec2.hpp"

namespace dae {
	class CircleColliderComponent final : public ColliderComponent
	{
	public:
		CircleColliderComponent(GameObject* pOwner, float radius, glm::vec2 offset = glm::vec2{0, 0});
		virtual ~CircleColliderComponent() = default;

		CircleColliderComponent(const CircleColliderComponent& other) = delete;
		CircleColliderComponent& operator=(const CircleColliderComponent& other) = delete;
		CircleColliderComponent(CircleColliderComponent&& other) = delete;
		CircleColliderComponent& operator=(CircleColliderComponent&& other) = delete;

	private:

		float m_Radius{};
		glm::vec2 m_Offset{};
	};
}

