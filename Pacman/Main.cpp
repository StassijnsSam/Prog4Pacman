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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Add background
	auto background = std::make_shared<dae::GameObject>();

	background.get()->AddComponent<dae::RenderComponent>("background.tga");

	scene.Add(background);

	//Add logo
	auto logo = std::make_shared<dae::GameObject>(glm::vec2{ 216, 180 });

	logo.get()->AddComponent<dae::RenderComponent>("logo.tga");

	scene.Add(logo);

	//Add text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<dae::GameObject>(glm::vec2{ 80, 20 });

	title.get()->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	title.get()->AddComponent<dae::RenderComponent>();

	scene.Add(title);

	//Add FPS counter
	auto fontFPS = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto FPSCounter = std::make_shared<dae::GameObject>(glm::vec2{ 10, 10 });

	FPSCounter.get()->AddComponent<dae::TextComponent>("0 FPS", fontFPS, SDL_Color{255, 255, 0});
	FPSCounter.get()->AddComponent<dae::FPSComponent>();
	FPSCounter.get()->AddComponent<dae::RenderComponent>();

	scene.Add(FPSCounter);

	//Add first ghost
	auto ghost1 = std::make_shared<dae::GameObject>(glm::vec2{ 310.f, 300.f });

	ghost1.get()->AddComponent<dae::RenderComponent>("GhostPink.png"); 
	ghost1.get()->AddComponent<dae::CircleColliderComponent>(10.0f);
	ghost1.get()->AddComponent<GhostComponent>();
	//	Create a starting state for the ghost
	auto ghost1StartState = std::make_unique<GhostNormalState>(ghost1.get(), "GhostPink.png");
	ghost1.get()->AddComponent<dae::StateMachine>(std::move(ghost1StartState));

	scene.Add(ghost1);

	//Add pacman
	auto pacman = std::make_shared<dae::GameObject>(glm::vec2{ 250.f, 300.f });

	pacman.get()->AddComponent<dae::RenderComponent>("Pacman.png");
	pacman.get()->AddComponent<dae::CircleColliderComponent>(10.0f);
	auto pacmanComponent = pacman.get()->AddComponent<PacmanComponent>();


	scene.Add(pacman);

	//Add a pellet
	auto pellet = std::make_shared<dae::GameObject>(glm::vec2{ 200.f, 300.f });

	pellet.get()->AddComponent<dae::RenderComponent>("pill.png");
	pellet.get()->AddComponent<dae::CircleColliderComponent>(3.0f);
	pellet.get()->AddComponent<LootComponent>(10);

	scene.Add(pellet);

	//Add a score display
	auto scoreDisplay = std::make_shared<dae::GameObject>(glm::vec2{ 20.f, 30.f });

	scoreDisplay.get()->AddComponent<dae::TextComponent>("0", fontFPS, SDL_Color{ 255, 0, 0 });
	scoreDisplay.get()->AddComponent<dae::RenderComponent>();
	auto scoreDisplayComponent = scoreDisplay.get()->AddComponent<ScoreDisplayComponent>();

	pacmanComponent->AddObserver(scoreDisplayComponent);
	
	scene.Add(scoreDisplay);

	//Add 3 life textures
	auto life1 = std::make_shared<dae::GameObject>(glm::vec2{ 20.f, 400.f });
	auto renderComponent1 = life1.get()->AddComponent<dae::RenderComponent>("life.png");
	scene.Add(life1);

	auto life2 = std::make_shared<dae::GameObject>(glm::vec2{ 50.f, 400.f });
	auto renderComponent2 = life2.get()->AddComponent<dae::RenderComponent>("life.png");
	scene.Add(life2);

	auto life3 = std::make_shared<dae::GameObject>(glm::vec2{ 80.f, 400.f });
	auto renderComponent3 = life3.get()->AddComponent<dae::RenderComponent>("life.png");
	scene.Add(life3);

	//	Put their renderComponents in a vector
	auto livesRenderComponents = std::vector<dae::RenderComponent*>();
	livesRenderComponents.emplace_back(renderComponent1);
	livesRenderComponents.emplace_back(renderComponent2);
	livesRenderComponents.emplace_back(renderComponent3);

	//Create a lives display
	auto livesDisplay = std::make_shared<dae::GameObject>();
	auto livesDisplayComponent = livesDisplay.get()->AddComponent<LivesDisplayComponent>(livesRenderComponents);
	scene.Add(livesDisplay);

	pacmanComponent->AddObserver(livesDisplayComponent);

	//Create controller
	dae::InputManager::GetInstance().CreateController();

	//Console player ghost1
	dae::InputManager::GetInstance().CreateConsoleCommand(
		dae::ButtonState::Hold, dae::XBoxController::ControllerButton::DPadLeft, 
		std::make_unique<dae::Move>(ghost1.get(), glm::vec2{-1, 0}, 500.f));
	dae::InputManager::GetInstance().CreateConsoleCommand(
		dae::ButtonState::Hold, dae::XBoxController::ControllerButton::DPadRight,
		std::make_unique<dae::Move>(ghost1.get(), glm::vec2{ 1, 0 }, 500.f));
	dae::InputManager::GetInstance().CreateConsoleCommand(
		dae::ButtonState::Hold, dae::XBoxController::ControllerButton::DPadUp,
		std::make_unique<dae::Move>(ghost1.get(), glm::vec2{ 0, -1 }, 500.f));
	dae::InputManager::GetInstance().CreateConsoleCommand(
		dae::ButtonState::Hold, dae::XBoxController::ControllerButton::DPadDown,
		std::make_unique<dae::Move>(ghost1.get(), glm::vec2{ 0, 1 }, 500.f));


	//Keyboard player ghost2
	dae::InputManager::GetInstance().CreateKeyboardCommand(
		dae::ButtonState::Hold, SDL_SCANCODE_LEFT,
		std::make_unique<dae::Move>(pacman.get(), glm::vec2{ -1, 0 }, 300.f));
	dae::InputManager::GetInstance().CreateKeyboardCommand(
		dae::ButtonState::Hold, SDL_SCANCODE_RIGHT,
		std::make_unique<dae::Move>(pacman.get(), glm::vec2{ 1, 0 }, 300.f));
	dae::InputManager::GetInstance().CreateKeyboardCommand(
		dae::ButtonState::Hold, SDL_SCANCODE_UP,
		std::make_unique<dae::Move>(pacman.get(), glm::vec2{ 0, -1 }, 300.f));
	dae::InputManager::GetInstance().CreateKeyboardCommand(
		dae::ButtonState::Hold, SDL_SCANCODE_DOWN,
		std::make_unique<dae::Move>(pacman.get(), glm::vec2{ 0, 1 }, 300.f));

	//Initialize the scene to link the components together (components that require other components to work)
	scene.Initialize();
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}