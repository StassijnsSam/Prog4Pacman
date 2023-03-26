#include <SDL.h>
#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
	UpdateConsoleInput();
	
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		
		UpdateKeyboardInput(e);

		//imGui (if needed)
	}

	return true;
}

void dae::InputManager::CreateController(int controllerIndex)
{
	//Put controller at the place of its index?
	m_pControllers.push_back(std::move(std::make_unique<XBoxController>(controllerIndex)));
}

void dae::InputManager::UpdateConsoleInput()
{
	for (const auto& pController : m_pControllers) {
		pController.get()->Update();

		//Commands need to work for multiple controllers now just for one
		for (auto& command : m_ConsoleCommands) {
			switch (command.first.first) {
			case ButtonState::Down:
				if (pController.get()->IsDownThisFrame(command.first.second)) {
					command.second.get()->Execute();
				}
				break;
			case ButtonState::Up:
				if (pController.get()->IsUpThisFrame(command.first.second)) {
					command.second.get()->Execute();
				}
				break;
			case ButtonState::Hold:
				if (pController.get()->IsPressed(command.first.second)) {
					command.second.get()->Execute();
				}
				break;
			}

		}
	}
}

void dae::InputManager::UpdateKeyboardInput(SDL_Event e)
{
	for (auto& command : m_KeyboardCommands)
	{
		auto key = e.key.keysym.scancode;

		if (command.first.second != key)
			continue;

		// Check press or release
		switch (e.type)
		{
		case SDL_KEYUP:
			if (command.first.first == ButtonState::Up)
			{
				command.second.get()->Execute();
			}
			break;

		case SDL_KEYDOWN:
			if (command.first.first == ButtonState::Down)
			{
				command.second.get()->Execute();
			}
			break;
		}
	}
}
