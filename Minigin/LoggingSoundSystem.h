#pragma once

#include "ISound.h"
#include <memory>
#include "string"

namespace dae {
	class LoggingSoundSystem final : public ISound
	{
	public:
		LoggingSoundSystem(std::unique_ptr<ISound>&& pSound);
		virtual ~LoggingSoundSystem() = default;

		virtual void Play(const std::string& soundName, const int volume) override;
		virtual void Stop() override;

	private:
		std::unique_ptr<ISound> m_pSound;
	};
}

