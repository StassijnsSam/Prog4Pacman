#pragma once
namespace dae {
	class ISound
	{
	public:
		virtual ~ISound() = default;

		virtual void Play(int soundID, const float volume) = 0;
		virtual void Stop(int soundID) = 0;
	};
}

