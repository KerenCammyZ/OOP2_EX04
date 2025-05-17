#pragma once
#include <SFML\Graphics.hpp>
class GameObject 
{
public:
	//constructor and destructor
	GameObject();
	explicit GameObject(std::unique_ptr<sf::Shape> shape);
	GameObject(const sf::Vector2f& position, std::unique_ptr<sf::Shape> shape);
	virtual ~GameObject() {};
	//copy constructor and assignment operator 
	GameObject(const GameObject& other);
	GameObject operator=(const GameObject& other);
	//draw object on the screen
	void draw(sf::RenderWindow& window);
	//virtual void update(float deltaTime) = 0;
	//virtual void handleInput(int key, int action) = 0;

	//setters and getters
	sf::Vector2f getLocation() const;
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getStartPosition() const;
	sf::Vector2f getOldPosition() const;
	sf::Shape& getShape() const;

	void setColor(const sf::Color& color);
	void setPosition(sf::Vector2f position);
	void setStartPosition();

	//handle collision with other game objects
	bool checkCollision(GameObject& unknownObj) const;

	//virtual void handleCollision(GameObject& unknownObj) = 0;
	//virtual void handleCollision(Enemy& enemy) {};
	//virtual void handleCollision(Player& player) {};
	
protected:
	int m_tileSize = 10; //can change later

	sf::Vector2f m_oldPosition;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_position;
	
	//sf::RectangleShape m_shape;
	std::unique_ptr<sf::Shape> m_shape;
};