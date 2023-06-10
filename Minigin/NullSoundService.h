#pragma once

#include "ISound.h"
#include "string"

namespace dae {
	class NullSoundService final : public ISound
	{
	public:
		NullSoundService() = default;
		virtual ~NullSoundService() = default;

		virtual void Play(const std::string& soundName, const int volume) override;
		virtual void Stop() override;
	};
}

