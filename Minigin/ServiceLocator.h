#pragma once

#include "ISound.h"
#include "NullSoundService.h"
#include <memory>

namespace dae {
	class ServiceLocator final
	{
    public:
        ServiceLocator(const ServiceLocator& other) = delete;
        ServiceLocator(ServiceLocator&& other) = delete;
        ServiceLocator& operator=(const ServiceLocator& other) = delete;
        ServiceLocator& operator=(ServiceLocator&& other) = delete;

        static void Provide(std::unique_ptr<dae::ISound>&& pSoundService);
        static ISound* GetSoundService();

    private:
        ServiceLocator() = default;
        ~ServiceLocator() = default;

        static std::unique_ptr<ISound> m_pSoundService;
	};
}

