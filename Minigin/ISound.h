#pragma once
namespace dae {
	class ISound
	{
	public:
		virtual ~ISound() = default;

		virtual void Play(const std::string& soundName, const float volume) = 0;
		virtual void Stop() = 0;
	};
}

