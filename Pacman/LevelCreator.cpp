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

void LevelCreator::CreateLevel(const PacmanLevel& level, dae::Scene& scene)
{
    //Level gets created from top to bottom, find the correct startPlace for topLeft
    float startPosX = (level.windowWidth - (level.gridWidth * level.gridElementSize)) / 2.0f;
    float startPosY = (level.windowHeight - (level.gridHeight * level.gridElementSize)) / 2.0f;

    int ghostNumber{ 1 };

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

                scene.Add(wall);

                break;
            }
            // Create a pellet
            case 2:
            {    
                auto pellet = std::make_shared<dae::GameObject>(
                    glm::vec2{ startPosX + col * level.gridElementSize, startPosY + row * level.gridElementSize });

                pellet.get()->AddComponent<dae::RenderComponent>("pill.png");
                pellet.get()->AddComponent<dae::CircleColliderComponent>(3.0f);
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
                ghost.get()->AddComponent<dae::CircleColliderComponent>(10.0f);
                ghost.get()->AddComponent<GhostComponent>();
                //	Create a starting state for the ghost
                auto ghostStartState = std::make_unique<GhostNormalState>(ghost.get(), texture);
                ghost.get()->AddComponent<dae::StateMachine>(std::move(ghostStartState));

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
                pacman.get()->AddComponent<dae::CircleColliderComponent>(10.0f);
                pacman.get()->AddComponent<PacmanComponent>();


                scene.Add(pacman);

                SetupKeyboardPlayer(pacman.get());
                break;
            }

            default:
                break;
            }
        }
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
