#pragma once
class Time
{
public:
	static Time& instance() {
		static Time* instance = new Time();
		return *instance;
	}

	float GetDeltaTime() { return m_DeltaTime;}
private:
	Time() {};

	float m_DeltaTime{};
};

