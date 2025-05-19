// LevelManager.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

struct LevelData {
    int requiredPercentage;
    int enemyCount;
};

class LevelManager {
private:
    std::string m_filePath;
    sf::Vector2u m_windowSize;
    int m_initialLives;
    std::ifstream m_fileStream;

public:
    LevelManager(const std::string& filePath);
    ~LevelManager();

    bool initialize();
    bool loadNextLevel(LevelData& levelData);

    sf::Vector2u getWindowSize() const;
    int getInitialLives() const;
};
