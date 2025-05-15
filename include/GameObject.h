#include <SFML\Graphics.hpp>
class GameObject 
{
public:
	GameObject(sf::Vector2f position);
	virtual ~GameObject();
	void setColor(const sf::Color& color);
	virtual void update(float deltaTime) = 0;
	virtual void render() = 0;
	virtual void handleInput(int key, int action) = 0;
private:
	int m_tileSize = 50;
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
};