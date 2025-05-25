#include "MovingObject.h"

MovingObject::MovingObject()
	: GameObject(std::make_unique<sf::RectangleShape>(sf::Vector2f(tileSize, tileSize))){}