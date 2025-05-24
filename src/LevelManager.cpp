// LevelManager.cpp
#include "LevelManager.h"
#include <sstream>
#include <iostream>

LevelManager::LevelManager(const std::string& filePath)
	: m_filePath(filePath), m_windowSize(800, 600), m_initialLives(3), m_enemyCount(0)
{
}

LevelManager::~LevelManager()
{
    if (m_fileStream.is_open()) {
        m_fileStream.close();
    }
}

bool LevelManager::initialize()
{
    m_fileStream.open(m_filePath);
    if (!m_fileStream.is_open()) {
        std::cerr << "Failed to open level file: " << m_filePath << std::endl;
        return false;
    }

    std::string line;
    if (std::getline(m_fileStream, line)) {
        std::istringstream iss(line);
        int width, height, lives;

        if (iss >> width >> height >> lives) {
            m_windowSize = sf::Vector2u(width, height);
            m_initialLives = lives;
            return true;
        }
    }

    return false;
}


bool LevelManager::loadNextLevel(LevelData& levelData)
{
    std::string line;
    if (std::getline(m_fileStream, line)) {
        std::istringstream iss(line);

        if (iss >> levelData.requiredPercentage >> levelData.enemyCount) {
            return true;
        }
    }
    return false;
}

sf::Vector2u LevelManager::getWindowSize() const
{
    return m_windowSize;
}

int LevelManager::getInitialLives() const
{
    return m_initialLives;
}

int LevelManager::getEnemyCount() const
{
    return m_enemyCount;
}
