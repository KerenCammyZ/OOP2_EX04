#pragma once  
#include "Board.h"  
#include "Player.h"  
#include "LevelManager.h" 
#include <string>  
#include <fstream>  
#include <SFML/Window.hpp>  
#include <SFML/Graphics.hpp>  
#include <iostream>  
#include <set>

class Controller  
{  
public:  
	// constructor and destructor
   Controller();  
   ~Controller() = default;  

   //other methods
   void run();
   void updatePlayerState();
   void handleEvents();
   void update();
   void draw();  
   void handleKeyPressed(sf::Keyboard::Key keyCode, sf::Time deltaTime);  
   void handleStats();
   void waitForSpace();
   void loadNextLevel(LevelData& levelData);
   void claimTerritory();
   void resetGame();

   // collision handling methods
   void checkBoundries(GameObject& obj) const;
   void handleCollisions();
   void handleFullTileEnemyCollisions();
   virtual void handleCollision(GameObject& unknownObj) {};
   virtual void handleCollision(Enemy& enemy) {};
   virtual void handleCollision(Player& player) {};
   virtual void handleCollision(Tile& tile) {};

private:  
   Board m_board; 
   Player m_player;  
   LevelManager m_levelManager; 
   LevelData m_currentLevelData;
   sf::RenderWindow m_window;
   std::vector<std::vector<std::pair<int, int>>> findEmptyRegions();
   std::vector<std::pair<int, int>> exploreRegion(int startRow, int startCol, std::set<std::pair<int, int>>& visited);
   bool regionContainsEnemy(const std::vector<std::pair<int, int>>& region);

   bool m_running{ false };
   int m_requiredPercentage{50};  // required to complete level

   sf::Font m_font;
   sf::Time m_deltaTime;  
   sf::Clock m_clock;
};