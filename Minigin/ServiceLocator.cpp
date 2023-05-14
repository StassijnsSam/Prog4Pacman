#include "ServiceLocator.h"

void dae::ServiceLocator::Initialize()
{
	m_pNullSoundService = new dae::NullSoundService();

	//Initially set the service to nullService
	m_pSoundService = m_pNullSoundService;
}

void dae::ServiceLocator::Provide(ISound* pSoundService)
{
	if (pSoundService == nullptr) {
		m_pSoundService = m_pNullSoundService;
	}
	else {
		m_pSoundService = pSoundService;
	}
}

dae::ISound* dae::ServiceLocator::GetSoundService()
{
	return m_pSoundService;
}
