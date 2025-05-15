#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <string>
#include <iostream>

class Controller
{
public:
	Controller();
	~Controller() = default;
	void run();
	void loadLevel(const std::string& fileName);
	void update();
	void render();
	void handleInput();

private:
	bool m_running{ false };
	sf::RenderWindow m_window{ sf::VideoMode(800, 600), "Xonix" };
};