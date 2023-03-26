#include "MoveCommands.h"
#include "GameObject.h"
#include "Time.h"
#include "MovementComponent.h"

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
	auto pMovement = m_pGameObject->GetComponent<MovementComponent>();

	if (pMovement == nullptr) {
		//No movement component was found
		return;
	}

	glm::vec2 direction{0, -1};
	pMovement->MoveInDirection(direction);
}

void dae::DownCommand::Execute()
{
	auto pMovement = m_pGameObject->GetComponent<MovementComponent>();

	if (pMovement == nullptr) {
		//No movement component was found
		return;
	}

	glm::vec2 direction{ 0, 1 };
	pMovement->MoveInDirection(direction);
}

void dae::LeftCommand::Execute()
{
	auto pMovement = m_pGameObject->GetComponent<MovementComponent>();

	if (pMovement == nullptr) {
		//No movement component was found
		return;
	}

	glm::vec2 direction{ -1, 0 };
	pMovement->MoveInDirection(direction);
}

void dae::RightCommand::Execute()
{
	auto pMovement = m_pGameObject->GetComponent<MovementComponent>();

	if (pMovement == nullptr) {
		//No movement component was found
		return;
	}

	glm::vec2 direction{ 1, 0 };
	pMovement->MoveInDirection(direction);
}
