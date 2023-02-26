#include "Transform.h"
#include "GameObject.h"

Transform::Transform(glm::vec2& origin, float rot)
{
	m_Position = origin;
	m_Rotation = rot;
}

void Transform::Update(GameObject&)
{
	//Empty
	//	Transform will be update elsewhere based on input or physics
	//	Got rid of formal parameter (name for gameObject)
}

void Transform::Render(GameObject&) const
{
	//Empty
}

void Transform::Recieve(int) const
{
}

const glm::vec2& Transform::GetPosition() const
{
	return m_Position;
}

float Transform::GetRotation() const
{
	return m_Rotation;
}

void Transform::SetRotation(float rot)
{
	m_Rotation = rot;
}

void Transform::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Transform::SetPosition(glm::vec2& pos)
{
	SetPosition(pos.x, pos.y);
}
