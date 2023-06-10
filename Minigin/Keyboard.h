#pragma once

#include <SDL.h>
#include <vector>

namespace dae {

	class Keyboard final
	{
	public:
		Keyboard();
		~Keyboard() = default;

		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) = delete;

		void Update();

		bool IsButtonPressedThisFrame(SDL_Scancode key) const;
		bool IsButtonReleasedThisFrame(SDL_Scancode key) const;
		bool IsButtonPressed(SDL_Scancode key) const;

	private:
		std::vector<Uint8> m_CurrentState{};
		std::vector<Uint8> m_PreviousState{};

		std::vector<Uint8> m_ButtonsPressedThisFrame{};
		std::vector<Uint8> m_ButtonsReleasedThisFrame{};
	};
}


