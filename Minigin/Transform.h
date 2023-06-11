#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace dae {

	class Transform final : public BaseComponent
	{
	public:
		Transform(GameObject* pOwner);
		Transform(GameObject* pOwner, const glm::vec2& origin, float rot = 0.f, float size = 1.f);
		virtual ~Transform() = default;

		Transform(const Transform& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render() const override;
		virtual void Recieve(int message) const override;

		const glm::vec2& GetWorldPosition();
		void UpdateWorldPosition();
		const glm::vec2& GetLocaPosition() const;
		void SetWorldPosition(float x, float y);
		void SetWorldPosition(const glm::vec2& pos);
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& pos);
		void AddLocalPosition(const glm::vec2& pos);

		float GetRotation() const;
		void SetRotation(float rot);
		void SetRotationFromDirection(const glm::vec2& direction);
		void SetDirection(const glm::vec2& direction);
		void AddRotation(float rot);

		void SetDirty();

	private:
		//Changed to 2D (Pac-man)
		glm::vec2 m_WorldPosition{};
		glm::vec2 m_LocalPosition{};
		bool m_IsDirty{ false };

		float m_Rotation{};
		float m_Size{};

		glm::vec2 m_Direction{};
	};
}

