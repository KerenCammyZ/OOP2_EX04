#pragma once
#include <SFML\Graphics.hpp>
#include "GlobalSizes.h"

class Enemy;
class Player;
class Boundry;
class Tile;

class GameObject 
{
public:
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
	sf::Vector2f getPosition() const;
	sf::Vector2f getStartPosition() const;
	sf::Vector2f getOldLocation() const;
	sf::Shape& getShape() const;
	sf::FloatRect getGlobalBounds() const;

	void setColor(const sf::Color& color);
	void setOutlineColor(const sf::Color& color);
	void setPosition(const sf::Vector2f& position);
	void setStartPosition(const sf::Vector2f& position);
	void setOldPosition(const sf::Vector2f& position);

	//handle collision with other game objects
	bool checkCollision(GameObject& unknownObj) const;

	virtual void handleCollision(GameObject& unknownObj) {};
	virtual void handleCollision(Enemy& enemy) {};
	virtual void handleCollision(Player& player) {};
	virtual void handleCollision(Tile& tile) {};

	
protected:
	sf::Vector2f m_oldPosition;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_position;
	
	std::unique_ptr<sf::Shape> m_shape;
};