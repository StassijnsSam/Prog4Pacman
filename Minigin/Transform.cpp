#include "Transform.h"
#include "GameObject.h"

dae::Transform::Transform(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

dae::Transform::Transform(GameObject* pOwner, const glm::vec2& origin, float rot)
	:BaseComponent(pOwner), m_Position{origin}, m_Rotation{rot}
{
}

void dae::Transform::Initialize()
{
}

void dae::Transform::Update()
{
	//Empty
	//	Transform will be update elsewhere based on input or physics
	//	Got rid of formal parameter (name for gameObject)
}

void dae::Transform::Render() const
{
	//Empty
}

void dae::Transform::Recieve(int) const
{
}

const glm::vec2& dae::Transform::GetPosition() const
{
	return m_Position;
}

float dae::Transform::GetRotation() const
{
	return m_Rotation;
}

void dae::Transform::SetRotation(float rot)
{
	m_Rotation = rot;
}

void dae::Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void dae::Transform::SetPosition(glm::vec2& pos)
{
	SetPosition(pos.x, pos.y);
}
