#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotatorComponent.h"
#include "InputManager.h"
#include "MoveCommands.h"
#include "MovementComponent.h"
#include "CircleColliderComponent.h"
#include "PacmanComponent.h"
#include "LootComponent.h"
#include "CollisionManager.h"
#include "ScoreDisplayComponent.h"
#include "GhostComponent.h"
#include "LivesDisplayComponent.h"
#include "StateMachine.h"
#include "GhostStates.h"
#include "SoundSystem.h"
#include "ServiceLocator.h"
#include "LevelLoader.h"
#include "LevelCreator.h"
#include "PacmanLevel.h"
#include "ResourceManager.h"

void load()
{
	std::shared_ptr<dae::Scene> versus = std::make_shared<dae::Scene>("Versus");
	dae::SceneManager::GetInstance().AddScene(versus);

	//Load level
	PacmanLevel level{};
	std::string levelPath = dae::ResourceManager::GetInstance().GetFullLevelPath("level.json");
	LevelLoader::LoadLevel(levelPath, level);
	LevelCreator::CreateLevel(level, *versus);

	//Initiliaze (so components link to each other)
	versus.get()->Initialize();

	////Add background
	//auto background = std::make_shared<dae::GameObject>();

	//background.get()->AddComponent<dae::RenderComponent>("background.tga");

	//scene.Add(background);

	////Add logo
	//auto logo = std::make_shared<dae::GameObject>(glm::vec2{ 216, 180 });

	//logo.get()->AddComponent<dae::RenderComponent>("logo.tga");

	//scene.Add(logo);

	////Add FPS counter
	//auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	//auto FPSCounter = std::make_shared<dae::GameObject>(glm::vec2{ 10, 10 });

	//FPSCounter.get()->AddComponent<dae::TextComponent>("0 FPS", fontFPS, SDL_Color{255, 255, 0});
	//FPSCounter.get()->AddComponent<dae::FPSComponent>();
	//FPSCounter.get()->AddComponent<dae::RenderComponent>();

	//scene.Add(FPSCounter);


	

	//Create sound service
	dae::ServiceLocator::Provide(std::make_unique<dae::SoundSystem>());

}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}