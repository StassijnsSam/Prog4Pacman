#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae {

	//class Texture2D;
	class Transform;

	class MovementComponent final : public BaseComponent
	{
	public:
		MovementComponent(GameObject* pOwner);
		MovementComponent(GameObject* pOwner, float movementSpeed);
		virtual ~MovementComponent() = default;

		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message) const override;

		void SetMovementSpeed(float movementSpeed);
		void MoveInDirection(glm::vec2 direction);

	private:
		float m_MovementSpeed{ 500.f };
		glm::vec2 m_Movement{};
		bool m_ShouldMove{ false };

		Transform* m_pTransform{};
	};
}

