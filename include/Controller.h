#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

class Controller
{
public:
	Controller() = default;
	~Controller() = default;
	void run();
	void loadLevel(const std::string& fileName);
	void update();
	void render();
	void handleEvents();

private:
	bool m_running{ false };
	sf::RenderWindow m_window{ sf::VideoMode(800, 600), "Xonix" };
};