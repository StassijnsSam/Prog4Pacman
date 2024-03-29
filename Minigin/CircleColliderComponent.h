#pragma once

#include "ColliderComponent.h"
#include "glm/vec2.hpp"

namespace dae {
	class CircleColliderComponent final : public ColliderComponent
	{
	public:
		CircleColliderComponent(GameObject* pOwner, float radius, bool isStatic = false, glm::vec2 offset = glm::vec2{0, 0});
		virtual ~CircleColliderComponent() = default;

		CircleColliderComponent(const CircleColliderComponent& other) = delete;
		CircleColliderComponent& operator=(const CircleColliderComponent& other) = delete;
		CircleColliderComponent(CircleColliderComponent&& other) = delete;
		CircleColliderComponent& operator=(CircleColliderComponent&& other) = delete;

		virtual bool IsColliding(ColliderComponent* other) override;

		float GetRadius();

	private:

		float m_Radius{};
		glm::vec2 m_Offset{};
	};
}

