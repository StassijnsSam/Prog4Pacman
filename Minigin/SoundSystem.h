#pragma once

#include "ISound.h"
#include <memory>
#include "string"

namespace dae {
	class SoundSystem final : public ISound
	{
		class SoundSystemImpl;
		std::unique_ptr<SoundSystemImpl> pImpl;

	public:
		SoundSystem();
		virtual ~SoundSystem() override;

		virtual void Play(const std::string& soundName, const float volume) override;
		virtual void Stop() override;
	};
}


