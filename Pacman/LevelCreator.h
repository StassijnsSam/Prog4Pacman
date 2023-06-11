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
	static void SetupPlayers();
};

