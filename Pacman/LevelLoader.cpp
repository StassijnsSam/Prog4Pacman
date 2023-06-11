#include "LevelLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <rapidjson.h>
#include <document.h>

bool LevelLoader::LoadLevel(const std::string& jsonPath, PacmanLevel& level)
{
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << jsonPath << std::endl;
        return false;
    }

    // Read the entire file content into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonString = buffer.str();

    // Parse the JSON string
    rapidjson::Document document;
    if (document.Parse(jsonString.c_str()).HasParseError()) {
        std::cerr << "Failed to parse JSON file: " << jsonPath << std::endl;
        return false;
    }

    // Extract the level data from the JSON document
    level.gridWidth = document["width"].GetInt();
    level.gridHeight = document["height"].GetInt();

    const rapidjson::Value& gridData = document["grid"];
    if (!gridData.IsArray()) {
        std::cerr << "Invalid grid data in JSON file: " << jsonPath << std::endl;
        return false;
    }

    for (const auto& row : gridData.GetArray()) {
        if (!row.IsArray()) {
            std::cerr << "Invalid row data in JSON file: " << jsonPath << std::endl;
            return false;
        }

        std::vector<int> rowData;
        for (const auto& element : row.GetArray()) {
            if (!element.IsInt()) {
                std::cerr << "Invalid element data in JSON file: " << jsonPath << std::endl;
                return false;
            }
            rowData.push_back(element.GetInt());
        }

        level.grid.push_back(rowData);
    }

    return true;
}
