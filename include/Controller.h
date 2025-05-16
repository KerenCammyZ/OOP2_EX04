#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <string>
#include <iostream>

#include "Board.h"

class Controller
{
public:
	Controller();
	~Controller() = default;
	void run();
	void loadLevel(const std::string& fileName);
	void update();
	void draw();

private:
	bool m_running{ false };
	sf::RenderWindow m_window{ sf::VideoMode(1600,1200), "Xonix" };
	Board m_board{ 50,50 };
};