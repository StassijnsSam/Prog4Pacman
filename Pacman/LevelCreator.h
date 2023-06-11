#pragma once

#include "PacmanLevel.h"
#include "Scene.h"

class LevelCreator
{
public:
	LevelCreator() = default;
	~LevelCreator() = default;

	static void CreateLevel(const PacmanLevel& level, dae::Scene& scene);

private:
	static void SetupKeyboardPlayer(dae::GameObject* pPlayer);
	static void SetupConsolePlayer(dae::GameObject* pPlayer);
};

