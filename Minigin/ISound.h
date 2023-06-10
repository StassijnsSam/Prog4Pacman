#pragma once

#include "string"

namespace dae {
	class ISound
	{
	public:
		virtual ~ISound() = default;

		virtual void Play(const std::string& soundName, const int volume) = 0;
		virtual void Stop() = 0;
	};
}

