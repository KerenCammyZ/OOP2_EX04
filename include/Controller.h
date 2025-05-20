#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Boundry.h"

class Controller
{
public:
	Controller();
	~Controller() = default;
	void run();
	void loadLevel(const std::string& fileName);
	void update();
	void draw();
	void handleKeyPressed(sf::Keyboard::Key keyCode, sf::Time deltaTime);

	virtual void handleCollision(GameObject& unknownObj) {};
	virtual void handleCollision(Enemy& enemy) {};
	virtual void handleCollision(Player& player) {};
	virtual void handleCollision(Boundry& boundry) {};
	virtual void handleCollision(Tile& tile) {};

private:
	sf::RenderWindow m_window{ sf::VideoMode(1000,1200), "Xonix" };
	Board m_board; //TODO: change to dynamic size
	Player m_player;
	Boundry m_boundry;


	bool m_running{ false };
	sf::Time m_deltaTime;
	sf::Clock m_clock;
};