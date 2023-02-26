#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

class Transform final : public BaseComponent
{
public:
	Transform() = default;
	virtual ~Transform() = default;

	Transform(const Transform& other) = delete;
	Transform& operator=(const Transform& other) = delete;
	Transform(Transform&& other) = delete;
	Transform& operator=(Transform&& other) = delete;

	virtual void Update(GameObject& gameObject) override;
	virtual void Render(GameObject& gameObject) const override;

	const glm::vec2& GetPosition() const;
	void SetPosition(float x, float y);
	void SetPosition(glm::vec2& pos);

	float GetRotation() const;
	void SetRotation(float rot);

private:
	//Changed to 2D (Pac-man)
	glm::vec2 m_Position{};
	float m_Rotation{};
};

