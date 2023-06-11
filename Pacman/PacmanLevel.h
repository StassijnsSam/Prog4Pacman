#pragma once

#include <vector>

struct PacmanLevel
{
	int gridWidth{};
	int gridHeight{};

	float gridElementSize{ 16.0f };

	const float windowWidth{ 640.f };
	const float windowHeight{ 480.f };

	std::vector<std::vector<int>> grid;
};

