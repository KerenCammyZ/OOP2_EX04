#include "Boundry.h"
#include "GlobalSizes.h"

Boundry::Boundry(int width, int height):m_width(width), m_height(height)
{
	m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(tileSize * width, tileSize * height));
	m_shape->setFillColor(sf::Color::Transparent);
}