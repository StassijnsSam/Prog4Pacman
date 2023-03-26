#include "MoveCommands.h"
#include "GameObject.h"
#include "Time.h"

dae::UpCommand::UpCommand(GameObject* pGameObject)
: Command(pGameObject)
{
}

dae::DownCommand::DownCommand(GameObject* pGameObject)
	: Command(pGameObject)
{
}

dae::LeftCommand::LeftCommand(GameObject* pGameObject)
	: Command(pGameObject)
{
}

dae::RightCommand::RightCommand(GameObject* pGameObject)
	: Command(pGameObject)
{
}

void dae::UpCommand::Execute()
{
	float movementSpeed = 500.f;

	auto pTransform = m_pGameObject->GetComponent<Transform>();

	if (pTransform == nullptr) {
		//No transform was found
		return;
	}

	glm::vec2 movement{0, -movementSpeed * Time::GetInstance().GetDeltaTime()};

	pTransform->SetLocalPosition(pTransform->GetLocaPosition() + movement);
}

void dae::DownCommand::Execute()
{
	float movementSpeed = 500.f;

	auto pTransform = m_pGameObject->GetComponent<Transform>();

	if (pTransform == nullptr) {
		//No transform was found
		return;
	}

	glm::vec2 movement{ 0, movementSpeed * Time::GetInstance().GetDeltaTime() };

	pTransform->SetLocalPosition(pTransform->GetLocaPosition() + movement);
}

void dae::LeftCommand::Execute()
{
	float movementSpeed = 500.f;

	auto pTransform = m_pGameObject->GetComponent<Transform>();

	if (pTransform == nullptr) {
		//No transform was found
		return;
	}

	glm::vec2 movement{ -movementSpeed * Time::GetInstance().GetDeltaTime(), 0 };

	pTransform->SetLocalPosition(pTransform->GetLocaPosition() + movement);
}

void dae::RightCommand::Execute()
{
	float movementSpeed = 500.f;

	auto pTransform = m_pGameObject->GetComponent<Transform>();

	if (pTransform == nullptr) {
		//No transform was found
		return;
	}

	glm::vec2 movement{ movementSpeed * Time::GetInstance().GetDeltaTime(), 0 };

	pTransform->SetLocalPosition(pTransform->GetLocaPosition() + movement);
}
