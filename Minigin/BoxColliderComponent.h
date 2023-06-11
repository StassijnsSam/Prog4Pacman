#pragma once
#pragma once

#include "ColliderComponent.h"
#include "glm/vec2.hpp"

namespace dae {
	class BoxColliderComponent final : public ColliderComponent
	{
	public:
		BoxColliderComponent(GameObject* pOwner, glm::vec2 size, bool isStatic = false, glm::vec2 offset = glm::vec2{ 0, 0 });
		virtual ~BoxColliderComponent() = default;

		BoxColliderComponent(const BoxColliderComponent& other) = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
		BoxColliderComponent(BoxColliderComponent&& other) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;

		virtual bool IsColliding(ColliderComponent* other) override;

		const glm::vec2& GetSize();

	private:

		glm::vec2 m_Size{};
		glm::vec2 m_Offset{};
	};
}


