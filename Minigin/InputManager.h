#pragma once
#include "Singleton.h"

namespace dae
{
	
	enum class ButtonState {
		Down,
		Up,
		Hold
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
	};

}
