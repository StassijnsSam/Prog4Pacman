#include "Timetracker.h"

float Time::GetDeltaTime()
{
	return m_DeltaTime;
}

float Time::GetElapsedTime()
{
	return m_ElapsedTime;
}

void Time::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
	m_ElapsedTime += deltaTime;
}
