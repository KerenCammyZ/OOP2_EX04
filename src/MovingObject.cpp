#include "MovingObject.h"

MovingObject::MovingObject()
	: GameObject(std::make_unique<sf::RectangleShape>(sf::Vector2f(m_tileSize, m_tileSize)))
{

}

