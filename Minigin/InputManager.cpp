#include <SDL.h>
#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		
		//imGui (if needed)
	}

	UpdateKeyboardInput();

	UpdateConsoleInput();

	return true;
}

void dae::InputManager::ClearKeyboardCommands()
{
	m_KeyboardCommands.clear();
}

void dae::InputManager::ClearConsoleCommands()
{
	m_ConsoleCommands.clear();
}

void dae::InputManager::CreateConsoleCommand(ButtonState state, XBoxController::ControllerButton button, std::unique_ptr<Command> command)
{
	ControllerKey key = std::pair{ state, button };
	m_ConsoleCommands.insert(std::pair{ key, std::move(command) });
}

void dae::InputManager::CreateKeyboardCommand(ButtonState state, SDL_Scancode button, std::unique_ptr<Command> command)
{
	KeyboardKey key = std::pair{ state, button };
	m_KeyboardCommands.insert(std::pair{ key, std::move(command) });
}

int dae::InputManager::CreateController()
{
	int controllerIndex =  static_cast<int>(m_pControllers.size()) - 1;
	m_pControllers.push_back(std::move(std::make_unique<XBoxController>(controllerIndex)));

	return controllerIndex;
}

dae::XBoxController* dae::InputManager::GetController(int controllerIndex) const
{
	//auto it = std::find_if(m_pControllers.begin(), m_pControllers.end(), [&controllerIndex](const std::unique_ptr<XBoxController> x) { return x.get()->GetControllerIndex() == controllerIndex; });

	////Controller with this id has not been found
	//if (it == m_pControllers.end()) {
	//	return nullptr;
	//}
	//else {
	//	return (*it).get();
	//}

	if (controllerIndex > static_cast<int>(m_pControllers.size())) {
		return nullptr;
	}
	else {
		return m_pControllers.at(controllerIndex).get();
	}
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

void dae::InputManager::UpdateKeyboardInput()
{
	m_Keyboard->Update();

	for (auto& command : m_KeyboardCommands)
	{
		switch (command.first.first)
		{
		case ButtonState::Up:
			if (m_Keyboard.get()->IsButtonReleasedThisFrame(command.first.second))
			{
				command.second.get()->Execute();
			}
			break;

		case ButtonState::Down:
			if (m_Keyboard.get()->IsButtonPressedThisFrame(command.first.second))
			{
				command.second.get()->Execute();
			}
			break;

		case ButtonState::Hold:
			if (m_Keyboard.get()->IsButtonPressed(command.first.second))
			{
				command.second.get()->Execute();
			}
			break;
		}
	}
}
