#include "Tile.h"

Tile::Tile() :
	GameObject(std::make_unique<sf::RectangleShape>(sf::Vector2f(m_tileSize, m_tileSize))){}

Tile Tile::operator=(const Tile& other)
{
	if (this != &other)
	{
		GameObject::operator=(other); // Call base class assignment operator  
	}
	return *this;
}