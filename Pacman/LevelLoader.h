#pragma once

#include <string>
#include "PacmanLevel.h"

class LevelLoader
{
public:
	LevelLoader() = default;
	~LevelLoader() = default;

	static bool LoadLevel(const std::string& jsonPath, PacmanLevel& level);
private:
};

