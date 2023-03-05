#include "Transform.h"
#include "GameObject.h"

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

	auto pParent = m_pOwner->GetParent();
	auto parentTransform = pParent->GetComponent<Transform>();
	if (pParent == nullptr) {
		m_WorldPosition = m_LocalPosition;
	}
	else {
		if (parentTransform != nullptr) {
			m_WorldPosition = parentTransform->GetWorldPosition() + m_LocalPosition;
		}
	}
	m_IsDirty = false;
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
}

void dae::Transform::SetWorldPosition(const float x, const float y)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
}

void dae::Transform::SetWorldPosition(const glm::vec2& pos)
{
	SetWorldPosition(pos.x, pos.y);
}

void dae::Transform::SetLocalPosition(const float x, const float y)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_IsDirty = true;
}

void dae::Transform::SetLocalPosition(const glm::vec2& pos)
{
	SetLocalPosition(pos.x, pos.y);
	m_IsDirty = true;
}
