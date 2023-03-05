#include "RotatorComponent.h"
#include "GameObject.h"
#include "Time.h"

#define M_PI 3.1415926535f

dae::RotatorComponent::RotatorComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
}

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float rotationSpeed, float radius)
	:BaseComponent(pOwner), m_RotationSpeed{rotationSpeed}, m_Radius{radius}
{
}

void dae::RotatorComponent::Initialize()
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
	m_Center = transform->GetLocaPosition();
}

void dae::RotatorComponent::Update()
{
	float deltaTime = Time::GetInstance().GetDeltaTime();
	if (m_pTransform == nullptr) {
		//transform is not set
		return;
	}

	m_Angle += m_RotationSpeed * deltaTime;
	if (m_Angle > 360.f) {
		m_Angle -= 360.f;
	}

	float angleRadians = (m_Angle * M_PI)/180.f;

	glm::vec2 newPosition = m_Center + m_Radius* glm::vec2{ cosf(angleRadians), sinf(angleRadians)};

	m_pTransform->SetLocalPosition(newPosition);
}

void dae::RotatorComponent::Render() const
{
}

void dae::RotatorComponent::Recieve(int) const
{
}

void dae::RotatorComponent::SetRotationSpeed(float rotationSpeed)
{
	m_RotationSpeed = rotationSpeed;
}
