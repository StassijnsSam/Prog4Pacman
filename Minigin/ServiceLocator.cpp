#include "ServiceLocator.h"

//Initialize as nullSound
std::unique_ptr<dae::ISound> dae::ServiceLocator::m_pSoundService{ std::make_unique<dae::NullSoundService>() };


void dae::ServiceLocator::Provide(std::unique_ptr<dae::ISound>&& pSoundService)
{
	if (pSoundService == nullptr) {
		m_pSoundService = std::make_unique<NullSoundService>();
	}
	else {
		m_pSoundService = std::move(pSoundService);
	}
}

dae::ISound* dae::ServiceLocator::GetSoundService()
{
	return m_pSoundService.get();
}
