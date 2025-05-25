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
public:
    LevelManager(const std::string& filePath);
    ~LevelManager();

    bool initialize();
    bool loadNextLevel(LevelData& levelData);

    sf::Vector2u getWindowSize() const;
    int getInitialLives() const;
    int getEnemyCount() const;

    void reset(LevelData& levelData);

private:
    int m_initialLives;
    int m_enemyCount;
    std::string m_filePath;
    sf::Vector2u m_windowSize;
    std::ifstream m_fileStream;
};
