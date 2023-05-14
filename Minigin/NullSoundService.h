#pragma once

#include "ISound.h";

namespace dae {
	class NullSoundService final : public ISound
	{
	public:
		NullSoundService() = default;
		virtual ~NullSoundService() = default;

		virtual void Play(int soundID, const float volume) override;
		virtual void Stop(int soundID) ;
	};
}

