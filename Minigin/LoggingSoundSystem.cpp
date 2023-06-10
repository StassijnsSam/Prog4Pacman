#include "LoggingSoundSystem.h"
#include <iostream>

dae::LoggingSoundSystem::LoggingSoundSystem(std::unique_ptr<ISound>&& pSound):
	m_pSound(std::move(pSound))
{
}

void dae::LoggingSoundSystem::Play(const std::string& soundName, const int volume)
{
	std::cout << "Playing sound " << soundName << " at Volume " << std::to_string(volume) << std::endl;

	m_pSound.get()->Play(soundName, volume);
}

void dae::LoggingSoundSystem::Stop()
{
	std::cout << "Stopping sound system" << std::endl;

	m_pSound.get()->Stop();
}
