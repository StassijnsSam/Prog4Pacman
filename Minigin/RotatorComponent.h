#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae {

	//class Texture2D;
	class Transform;

	class RotatorComponent final : public BaseComponent
	{
	public:
		RotatorComponent(GameObject* pOwner);
		RotatorComponent(GameObject* pOwner, float rotationSpeed, float radius);
		virtual ~RotatorComponent() = default;

		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message) const override;

		void SetRotationSpeed(float rotationSpeed);
	private:
		float m_RotationSpeed{90.f};
		float m_Radius{ 1.0f };
		float m_Angle{ 0.f };
		Transform* m_pTransform{ nullptr };
		glm::vec2 m_Center{};
	};
}

