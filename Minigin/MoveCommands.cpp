#include "MoveCommands.h"
#include "GameObject.h"
#include "Time.h"
#include "MovementComponent.h"
#include "Timetracker.h"


dae::Move::Move(GameObject* pGameObject, const glm::vec2& dir, float moveSpeed):
	m_pGameObject{pGameObject}, m_Direction{dir}, m_MoveSpeed{moveSpeed}
{
}

void dae::Move::Execute()
{
	auto movement = m_Direction * m_MoveSpeed * Time::GetInstance().GetDeltaTime();

	m_pGameObject->GetTransform()->AddLocalPosition(movement);
}
