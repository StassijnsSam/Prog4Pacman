#include "Transform.h"
#include "GameObject.h"
#include <cmath>
#define _USE_MATH_DEFINES

#ifndef M_PI
constexpr double M_PI = 3.14159265358979323846;
#endif

dae::Transform::Transform(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

dae::Transform::Transform(GameObject* pOwner, const glm::vec2& origin, float rot, float size)
	:BaseComponent(pOwner), m_WorldPosition{origin}, m_Rotation{rot}, m_Size{size}, m_LocalPosition{origin}
{
}

void dae::Transform::Initialize()
{
}

void dae::Transform::Update()
{
}

void dae::Transform::Render() const
{
	//Empty
}

void dae::Transform::Recieve(int) const
{
}

const glm::vec2& dae::Transform::GetWorldPosition()
{
	if (m_IsDirty) {
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

void dae::Transform::UpdateWorldPosition()
{
	if (m_pOwner == nullptr) {
		//Owner not set correctly
		return;
	}

	m_IsDirty = false;

	auto pParent = m_pOwner->GetParent();
	if (pParent == nullptr) {
		m_WorldPosition = m_LocalPosition;
		return;
	}

	auto parentTransform = pParent->GetComponent<Transform>();
	
	if (parentTransform != nullptr) {
		m_WorldPosition = parentTransform->GetWorldPosition() + m_LocalPosition;
	}
}

const glm::vec2& dae::Transform::GetLocaPosition() const
{
	return m_LocalPosition;
}


float dae::Transform::GetRotation() const
{
	return m_Rotation;
}

void dae::Transform::SetRotation(float rot)
{
	m_Rotation = rot;
}

void dae::Transform::SetRotationFromDirection(const glm::vec2& direction)
{
	SetDirection(direction);
	
	float angleRadians = std::atan2(direction.y, direction.x);

	m_Rotation = angleRadians * 180.f / static_cast<float>(M_PI);
}

void dae::Transform::SetDirection(const glm::vec2& direction)
{
	m_Direction = direction;
}

const glm::vec2& dae::Transform::GetDirection()
{
	return m_Direction;
}

void dae::Transform::AddRotation(float rot)
{
	m_Rotation += rot;
	//keep it limited to 360 degrees
	if (m_Rotation > 360.f) {
		m_Rotation -= 360.f;
	}
}

void dae::Transform::SetDirty()
{
	m_IsDirty = true;

	if (m_pOwner == nullptr) {
		//Owner is not set correctly
		return;
	}

	auto children = GetOwner()->GetChildren();
	for (auto child : children)
	{
		auto childTransform = child->GetComponent<Transform>();
		if (childTransform == nullptr) {
			continue;
		}

		childTransform->SetDirty();
	}
}

void dae::Transform::SetWorldPosition(const float x, const float y)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	SetDirty();
}

void dae::Transform::SetWorldPosition(const glm::vec2& pos)
{
	SetWorldPosition(pos.x, pos.y);
	SetDirty();
}

void dae::Transform::SetLocalPosition(const float x, const float y)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	SetDirty();
}

void dae::Transform::SetLocalPosition(const glm::vec2& pos)
{
	SetLocalPosition(pos.x, pos.y);
	SetDirty();
}

void dae::Transform::AddLocalPosition(const glm::vec2& pos)
{
	SetDirty();

	m_LocalPosition += pos;
}
