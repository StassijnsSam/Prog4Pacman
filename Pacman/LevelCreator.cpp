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
                break;
            }

            default:
                break;
            }
        }
    }

    SetupPlayers();
}

void LevelCreator::SetupPlayers()
{
    //For now locked to versus but depending on different mode this would do different things
}
