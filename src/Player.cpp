#include "Player.h"
#include "MovingObject.h"

Player::Player()
{
	m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(m_tileSize, m_tileSize));
	setColor(sf::Color::Magenta);
}