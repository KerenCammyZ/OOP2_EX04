#include "Enemy.h"

Enemy::Enemy()
{
	m_shape = std::make_unique<sf::CircleShape>(m_tileSize / 2.0f);
	m_shape->setFillColor(sf::Color::Red);
}