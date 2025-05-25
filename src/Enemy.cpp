#include "Enemy.h"
#include <FullTile.h>
#include <iostream>

Enemy::Enemy()
	: m_speed{ 300.f }, m_direction{1,1}
{
	m_shape = std::make_unique<sf::CircleShape>(tileSize / 2.0f);
    m_shape->setFillColor(sf::Color::Red);
}

void Enemy::move(sf::Time deltaTime)
{
	setOldPosition(m_shape->getPosition());
	sf::Vector2f newPos = getPosition() + m_direction * m_speed * deltaTime.asSeconds();
	setPosition(newPos);
	
}

void Enemy::setDirection(const sf::Vector2f direction)
{
	m_direction = direction;
}

sf::Vector2f Enemy::getDirection() const
{
	return m_direction;
}

// Handle fullTile Collision
void Enemy::handleCollision(Tile& fullTile)
{
	// Revert to previous position to avoid getting stuck
	setPosition(getOldLocation());

	// Determine which axis to reverse based on movement direction
	sf::Vector2f currentPos = getPosition();
	sf::Vector2f tileCenter = sf::Vector2f(
		fullTile.getGlobalBounds().left + fullTile.getGlobalBounds().width / 2,
		fullTile.getGlobalBounds().top + fullTile.getGlobalBounds().height / 2
	);

	// Reverse the axis that would move us away from the tile center
	if (abs(currentPos.x - tileCenter.x) > abs(currentPos.y - tileCenter.y)) {
		m_direction.x = -m_direction.x;
	}
	else {
		m_direction.y = -m_direction.y;
	}
}