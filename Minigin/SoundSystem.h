#pragma once

#include "ISound.h"
#include <memory>
#include "string"

namespace dae {
	class SoundSystem final : public ISound
	{
		class SoundSystemImpl;
		SoundSystemImpl* pImpl;

	public:
		SoundSystem();
		virtual ~SoundSystem();

		virtual void Play(const std::string& soundName, const int volume) override;
		virtual void Stop() override;
	};
}


