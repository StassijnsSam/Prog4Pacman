#pragma once
#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	float GetElapsedTime() {
		return m_ElapsedTime;
	}

	void SetElapsedTime(float elapsedTime) {
		m_ElapsedTime = elapsedTime;
	}
private:
	float m_ElapsedTime{ 0.f };
};

