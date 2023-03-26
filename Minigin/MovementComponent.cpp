#include "MovementComponent.h"
#include "GameObject.h"
#include "Time.h"

dae::MovementComponent::MovementComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{

}

dae::MovementComponent::MovementComponent(GameObject* pOwner, float movementSpeed)
	:BaseComponent(pOwner), m_MovementSpeed{movementSpeed}
{
}

void dae::MovementComponent::Initialize()
{
	if (m_pOwner == nullptr) {
		//Owner not set correctly
		return;
	}

	auto transform = m_pOwner->GetComponent<Transform>();
	if (transform == nullptr) {
		//owner does not have a transform
		return;
	}

	m_pTransform = transform;
}

void dae::MovementComponent::Update()
{
	if (m_ShouldMove) {
		m_ShouldMove = false;

		if (m_pTransform == nullptr) {
			//There is no transform
			return;
		}

		m_pTransform->AddLocalPosition(m_Movement);
	}
}

void dae::MovementComponent::Render() const
{
}

void dae::MovementComponent::Recieve(int) const
{
}

void dae::MovementComponent::SetMovementSpeed(float movementSpeed)
{
	m_MovementSpeed = movementSpeed;
}

void dae::MovementComponent::MoveInDirection(glm::vec2 direction)
{
	m_ShouldMove = true;

	m_Movement = direction * m_MovementSpeed * Time::GetInstance().GetDeltaTime();
}
