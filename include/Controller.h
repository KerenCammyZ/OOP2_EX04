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
   Controller();  
   ~Controller() = default;  
   void run();
   void checkBoundries(GameObject& obj) const;
   void updatePlayerState();
   void handleEvents();
   void update(LevelData& levelData);
   void draw();  
   void handleKeyPressed(sf::Keyboard::Key keyCode, sf::Time deltaTime);  
   void handleStats();

   void waitScreen(const std::string& displayMessage);
   void showLevelCompleteScreen();
   void loadNextLevel(LevelData& levelData);
   void claimTerritory();

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
   sf::RenderWindow m_window;
   std::vector<std::vector<std::pair<int, int>>> findEmptyRegions();
   std::vector<std::pair<int, int>> exploreRegion(int startRow, int startCol, std::set<std::pair<int, int>>& visited);
   bool regionContainsEnemy(const std::vector<std::pair<int, int>>& region);

   //int m_lives{3}; // get set from Player
   //bool m_paused{ false };
   bool m_running{ false };  // defines game state
   int m_score = 0;
   int m_requiredPercentage{ 50 };  // required to complete level

   sf::Font m_font;
   sf::Time m_deltaTime;  
   sf::Clock m_clock;
};