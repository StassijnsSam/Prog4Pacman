#include "LevelCreator.h"
#include <memory>
#include "GameObject.h"
#include "RenderComponent.h"
#include "CircleColliderComponent.h"
#include "LootComponent.h"
#include "GhostComponent.h"
#include "StateMachine.h"
#include "GhostStates.h"
#include "PacmanComponent.h"
#include "InputManager.h"
#include "MoveCommands.h"
#include "BoxColliderComponent.h"
#include "WallComponent.h"
#include "TextComponent.h"
#include "LivesDisplayComponent.h"
#include "ResourceManager.h"
#include "ScoreDisplayComponent.h"

void LevelCreator::CreateLevel(const PacmanLevel& level, dae::Scene& scene)
{
    //Level gets created from top to bottom, find the correct startPlace for topLeft
    float startPosX = (level.windowWidth - (level.gridWidth * level.gridElementSize)) / 2.0f;
    float startPosY = (level.windowHeight - (level.gridHeight * level.gridElementSize)) / 2.0f;

    int ghostNumber{ 1 };
    std::vector<GhostComponent*> ghostComponents{};
    PacmanComponent* pacmanComponent{};

    //Loop over the levelGrid and create all the needed gameObjects
    for (int row{ 0 }; row < level.gridHeight; ++row) {
        for (int col{ 0 }; col < level.gridWidth; ++col) {
            auto element = level.grid.at(row).at(col);

            switch (element)
            {
            // Create a wall
            case 1:
            {
                auto wall = std::make_shared<dae::GameObject>(
                    glm::vec2{ startPosX + col * level.gridElementSize, startPosY + row * level.gridElementSize });

                wall.get()->AddComponent<dae::RenderComponent>("wall.png");
                //Walls are static, so pass true
                //wall.get()->AddComponent<dae::BoxColliderComponent>(glm::vec2{8.0f, 8.0f}, true);
                //wall.get()->AddComponent<WallComponent>();

                scene.Add(wall);

                break;
            }
            // Create a pellet
            case 2:
            {    
                auto pellet = std::make_shared<dae::GameObject>(
                    glm::vec2{ startPosX + col * level.gridElementSize, startPosY + row * level.gridElementSize });

                pellet.get()->AddComponent<dae::RenderComponent>("pill.png");
                //Pellets are static, so pass true
                pellet.get()->AddComponent<dae::CircleColliderComponent>(3.0f, true);
                pellet.get()->AddComponent<LootComponent>(10);

                scene.Add(pellet);

                break;
            }
            // Create a power pellet
            case 3:
            {
                auto powerPellet = std::make_shared<dae::GameObject>(
                    glm::vec2{ startPosX + col * level.gridElementSize, startPosY + row * level.gridElementSize });

                powerPellet.get()->AddComponent<dae::RenderComponent>("boost.png");
                powerPellet.get()->AddComponent<dae::CircleColliderComponent>(3.0f);
                powerPellet.get()->AddComponent<LootComponent>(50, true);

                scene.Add(powerPellet);

                break;
            }
            case 6:
            // Create a ghost
            {
                auto ghost = std::make_shared<dae::GameObject>(
                    glm::vec2{ startPosX + col * level.gridElementSize, startPosY + row * level.gridElementSize });

                std::string texture = "ghost" + std::to_string(ghostNumber) + ".png";

                ghost.get()->AddComponent<dae::RenderComponent>(texture);
                ghost.get()->AddComponent<dae::CircleColliderComponent>(8.0f);
                auto ghostComponent = ghost.get()->AddComponent<GhostComponent>();
                //	Create a starting state for the ghost
                auto ghostStartState = std::make_unique<GhostNormalState>(ghost.get(), texture);
                ghost.get()->AddComponent<dae::StateMachine>(std::move(ghostStartState));

                ghostComponents.emplace_back(ghostComponent);

                scene.Add(ghost);

                //Make the first ghost the console player
                if (ghostNumber == 1) {
                    SetupConsolePlayer(ghost.get());
                }

                ++ghostNumber;

                break;
            }
            // Create pacman
            case 7: {
                auto pacman = std::make_shared<dae::GameObject>(
                    glm::vec2{ startPosX + col * level.gridElementSize, startPosY + row * level.gridElementSize });

                pacman.get()->AddComponent<dae::RenderComponent>("Pacman.png");
                pacman.get()->AddComponent<dae::CircleColliderComponent>(8.0f);
                pacmanComponent = pacman.get()->AddComponent<PacmanComponent>();


                scene.Add(pacman);

                SetupKeyboardPlayer(pacman.get());
                SetupPlayerHud(pacman.get(), scene);
                break;
            }

            default:
                break;
            }
        }
    }

    //Link the ghosts as observers
    for (auto ghostComponent : ghostComponents) {
        pacmanComponent->AddObserver(ghostComponent);
    }
}

void LevelCreator::SetupKeyboardPlayer(dae::GameObject* pPlayer)
{
    const float movementSpeed{ 100.f };
    
    dae::InputManager::GetInstance().CreateKeyboardCommand(
    	dae::ButtonState::Hold, SDL_SCANCODE_LEFT,
    	std::make_unique<dae::Move>(pPlayer, glm::vec2{ -1, 0 }, movementSpeed));
    dae::InputManager::GetInstance().CreateKeyboardCommand(
    	dae::ButtonState::Hold, SDL_SCANCODE_RIGHT,
    	std::make_unique<dae::Move>(pPlayer, glm::vec2{ 1, 0 }, movementSpeed));
    dae::InputManager::GetInstance().CreateKeyboardCommand(
    	dae::ButtonState::Hold, SDL_SCANCODE_UP,
    	std::make_unique<dae::Move>(pPlayer, glm::vec2{ 0, -1 }, movementSpeed));
    dae::InputManager::GetInstance().CreateKeyboardCommand(
    	dae::ButtonState::Hold, SDL_SCANCODE_DOWN,
    	std::make_unique<dae::Move>(pPlayer, glm::vec2{ 0, 1 }, movementSpeed));
    

}

void LevelCreator::SetupConsolePlayer(dae::GameObject* pPlayer)
{
    //Create controller
    dae::InputManager::GetInstance().CreateController();

    const float movementSpeed{ 100.f };

    //Console player ghost1
    dae::InputManager::GetInstance().CreateConsoleCommand(
    	dae::ButtonState::Hold, dae::XBoxController::ControllerButton::DPadLeft, 
    	std::make_unique<dae::Move>(pPlayer, glm::vec2{-1, 0}, movementSpeed));
    dae::InputManager::GetInstance().CreateConsoleCommand(
    	dae::ButtonState::Hold, dae::XBoxController::ControllerButton::DPadRight,
    	std::make_unique<dae::Move>(pPlayer, glm::vec2{ 1, 0 }, movementSpeed));
    dae::InputManager::GetInstance().CreateConsoleCommand(
    	dae::ButtonState::Hold, dae::XBoxController::ControllerButton::DPadUp,
    	std::make_unique<dae::Move>(pPlayer, glm::vec2{ 0, -1 }, movementSpeed));
    dae::InputManager::GetInstance().CreateConsoleCommand(
    	dae::ButtonState::Hold, dae::XBoxController::ControllerButton::DPadDown,
    	std::make_unique<dae::Move>(pPlayer, glm::vec2{ 0, 1 }, movementSpeed));
}

void LevelCreator::SetupPlayerHud(dae::GameObject* pPlayer, dae::Scene& scene)
{
    auto pacmanComponent = pPlayer->GetComponent<PacmanComponent>();
    if (!pacmanComponent) {
        return;
    }
    
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
    //Add a score display
    auto scoreDisplay = std::make_shared<dae::GameObject>(glm::vec2{ 20.f, 30.f });

    scoreDisplay.get()->AddComponent<dae::TextComponent>("0", font, SDL_Color{ 255, 0, 0 });
    scoreDisplay.get()->AddComponent<dae::RenderComponent>();
    auto scoreDisplayComponent = scoreDisplay.get()->AddComponent<ScoreDisplayComponent>();

    pacmanComponent->AddObserver(scoreDisplayComponent);
    
    scene.Add(scoreDisplay);

    //Add 3 life textures
    auto life1 = std::make_shared<dae::GameObject>(glm::vec2{ 20.f, 450.f });
    auto renderComponent1 = life1.get()->AddComponent<dae::RenderComponent>("pacman.png");
    scene.Add(life1);

    auto life2 = std::make_shared<dae::GameObject>(glm::vec2{ 20.f, 430.f });
    auto renderComponent2 = life2.get()->AddComponent<dae::RenderComponent>("pacman.png");
    scene.Add(life2);

    auto life3 = std::make_shared<dae::GameObject>(glm::vec2{ 20.f, 410.f });
    auto renderComponent3 = life3.get()->AddComponent<dae::RenderComponent>("pacman.png");
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
}
