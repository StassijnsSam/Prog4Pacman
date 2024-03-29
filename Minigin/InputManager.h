#pragma once
#include "Singleton.h"
#include "XBoxController.h"
#include <map>
#include <vector>
#include <memory>
#include "Command.h"
#include "Keyboard.h"

namespace dae
{
	class GameObject;
	
	enum class ButtonState {
		Down,
		Up,
		Hold
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager() = default;

		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
		
		bool ProcessInput();

		void ClearKeyboardCommands();
		void ClearConsoleCommands();

		void CreateConsoleCommand(ButtonState state, XBoxController::ControllerButton button, std::unique_ptr<Command> command);

		void CreateKeyboardCommand(ButtonState state, SDL_Scancode button, std::unique_ptr<Command> command);

		int CreateController();
		XBoxController* GetController(int controllerIndex) const;

	private:
		using ControllerKey = std::pair<ButtonState, XBoxController::ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;

		ControllerCommandsMap m_ConsoleCommands{};

		using KeyboardKey = std::pair<ButtonState, SDL_Scancode>;
		using KeyboardCommandsMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		KeyboardCommandsMap m_KeyboardCommands{};

		//Initialize keyboard
		std::unique_ptr<Keyboard> m_Keyboard{ std::make_unique<Keyboard>() };

		std::vector<std::unique_ptr<XBoxController>> m_pControllers{};

		void UpdateConsoleInput();
		void UpdateKeyboardInput();
	};
}
