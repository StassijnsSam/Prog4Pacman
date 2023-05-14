#pragma once

#include "ISound.h"
#include "NullSoundService.h"

namespace dae {
	class ServiceLocator final
	{
    public:
        ServiceLocator(const ServiceLocator& other) = delete;
        ServiceLocator(ServiceLocator&& other) = delete;
        ServiceLocator& operator=(const ServiceLocator& other) = delete;
        ServiceLocator& operator=(ServiceLocator&& other) = delete;

        static void Initialize();
        static void Provide(ISound* pSoundService);
        static ISound* GetSoundService();

        static void DestroySoundService();

    private:
        ServiceLocator() = default;
        ~ServiceLocator() = default;

        static ISound* m_pSoundService;
        static NullSoundService m_pNullSoundService;
	};
}

