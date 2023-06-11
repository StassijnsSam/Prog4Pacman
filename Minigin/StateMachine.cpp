#include "StateMachine.h"

dae::StateMachine::StateMachine(GameObject* pOwner, std::unique_ptr<BaseState>&& startState)
	:BaseComponent(pOwner), m_pCurrentState(std::move(startState))
{
}

void dae::StateMachine::Initialize()
{
}

void dae::StateMachine::Update()
{
	m_pCurrentState.get()->Update();
}

void dae::StateMachine::Render() const
{
}

void dae::StateMachine::Recieve(int) const
{
}

void dae::StateMachine::FixedUpdate()
{
	m_pCurrentState.get()->FixedUpdate();
}

void dae::StateMachine::UpdateState(std::unique_ptr<BaseState>&& state)
{
	m_pCurrentState.get()->Exit();

	m_pCurrentState = std::move(state);

	m_pCurrentState.get()->Enter();
}
