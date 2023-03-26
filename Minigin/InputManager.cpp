#include <SDL.h>
#include "InputManager.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
	}

	return true;
}

void dae::InputManager::CreateController(int controllerIndex)
{
	//Put controller at the place of its index?
	m_pControllers.push_back(std::move(std::make_unique<XBoxController>(controllerIndex)));
}
