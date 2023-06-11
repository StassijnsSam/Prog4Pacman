#pragma once

#include "PacmanLevel.h"
#include "Scene.h"
#include "glm/vec2.hpp"

class LevelCreator
{
public:
	LevelCreator() = default;
	~LevelCreator() = default;

	static void CreateLevel(const PacmanLevel& level, dae::Scene& scene);

private:
	static void SetupKeyboardPlayer(dae::GameObject* pPlayer);
	static void SetupConsolePlayer(dae::GameObject* pPlayer);
	static void SetupPlayerHud(dae::GameObject* pPlayer, dae::Scene& scene);
};

