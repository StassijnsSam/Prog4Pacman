#pragma once

#include <vector>

struct PacmanLevel
{
	int gridWidth{};
	int gridHeight{};

	float gridSize{ 5.0f };

	std::vector<std::vector<int>> grid;
};

