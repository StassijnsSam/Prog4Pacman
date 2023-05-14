#include "ServiceLocator.h"

void dae::ServiceLocator::Initialize()
{
	m_pNullSoundService = dae::NullSoundService();

	//Initially set the service to nullService
	m_pSoundService = &m_pNullSoundService;
}

void dae::ServiceLocator::Provide(ISound* pSoundService)
{
	if (pSoundService == nullptr) {
		m_pSoundService = &m_pNullSoundService;
	}
	else {
		m_pSoundService = pSoundService;
	}
}

dae::ISound* dae::ServiceLocator::GetSoundService()
{
	return m_pSoundService;
}

void dae::ServiceLocator::DestroySoundService()
{
	if (m_pSoundService != &m_pNullSoundService) {
		delete m_pSoundService;
		m_pSoundService = &m_pNullSoundService;
	}
}
