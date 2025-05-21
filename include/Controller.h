#pragma once  
#include "Board.h"  
#include "Player.h"  
#include "LevelManager.h" 
#include <string>  
#include <fstream>  
#include <SFML/Window.hpp>  
#include <SFML/Graphics.hpp>  
#include <iostream>  

class Controller  
{  
public:  
   Controller();  
   ~Controller() = default;  
   void run();
   void checkBoundries(GameObject& obj) const;
   void update();
   void draw();  
   void handleKeyPressed(sf::Keyboard::Key keyCode, sf::Time deltaTime);  
   //void loadLevel(const std::string& fileName);  

   void waitForSpace();  

   void handleCollisions();
   virtual void handleCollision(GameObject& unknownObj) {};
   virtual void handleCollision(Enemy& enemy) {};
   virtual void handleCollision(Player& player) {};
   virtual void handleCollision(Tile& tile) {};

private:  
   Board m_board; 
   Player m_player;  
   LevelManager m_levelManager;  
   sf::RenderWindow m_window; // { sf::VideoMode(1000, 1200), "Xonix" }; 

   int m_lives{3};
   bool m_running{ false };  // defines game state
   int m_requiredPercentage{50};  // required to complete level
   sf::Time m_deltaTime;  
   sf::Clock m_clock;
};