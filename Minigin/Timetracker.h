#pragma once
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	float GetDeltaTime();
	float GetElapsedTime();
	void Update(float deltaTime);
private:
	float m_DeltaTime{ 0.f };
	float m_ElapsedTime{ 0.f };
};

