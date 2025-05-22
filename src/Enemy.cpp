#include "Enemy.h"
#include <FullTile.h>
#include <iostream>

Enemy::Enemy()
	: m_speed{ 300.f }, m_direction{1,1}
{
	m_shape = std::make_unique<sf::CircleShape>(tileSize / 2.0f);
    m_shape->setFillColor(sf::Color::Red);
	//m_shape->setOrigin(tileSize / 2.0f, tileSize / 2.0f);


    void setPosition(sf::Vector2f position);
    void setStartPosition();
    void setLocation(const sf::Vector2f & position);
    void setOldPosition(const sf::Vector2f & position);
}

void Enemy::move(sf::Time deltaTime)
{
	setOldPosition(getLocation());
	setPosition(getLocation() + m_direction * m_speed * deltaTime.asSeconds());

}


void Enemy::handleCollision(Tile& fullTile)
{
	sf::FloatRect tileBounds = fullTile.getGlobalBounds();
	sf::FloatRect enemyBounds = getGlobalBounds();
	// Calculate overlap amounts on each axis
	float overlapLeft = (enemyBounds.left + enemyBounds.width) - tileBounds.left;
	float overlapRight = (tileBounds.left + tileBounds.width) - enemyBounds.left;
	float overlapTop = (enemyBounds.top + enemyBounds.height) - tileBounds.top;
	float overlapBottom = (tileBounds.top + tileBounds.height) - enemyBounds.top;

	// Find the smallest overlap to determine collision direction
	float minOverlapX = std::min(overlapLeft, overlapRight);
	float minOverlapY = std::min(overlapTop, overlapBottom);

	// Determine collision direction based on smallest overlap
	if (minOverlapX < minOverlapY) {
		// Horizontal collision (left or right)
		if (overlapLeft < overlapRight) {
			// Collision from the left side of the tile
			setPosition(sf::Vector2f(tileBounds.left - enemyBounds.width, getLocation().y));
			std::cout << "Enemy collided at " << getLocation().x << getLocation().y << std::endl;
			std::cout << "Enemy direction " << getDirection().x << getDirection().y << std::endl;
		}
		else {
			// Collision from the right side of the tile
			setPosition(sf::Vector2f(tileBounds.left + tileBounds.width, getLocation().y));
			std::cout << "Enemy collided at " << getLocation().x << getLocation().y << std::endl;
			std::cout << "Enemy direction " << getDirection().x << getDirection().y << std::endl;
		}
		// Reverse horizontal direction
		m_direction.x = -m_direction.x;
	}
	else {
		// Vertical collision (top or bottom)
		if (overlapTop < overlapBottom) {
			// Collision from the top side of the tile
			setPosition(sf::Vector2f(getLocation().x, tileBounds.top - enemyBounds.height));
			std::cout << "Enemy collided at " << getLocation().x << getLocation().y << std::endl;
			std::cout << "Enemy direction " << getDirection().x << getDirection().y << std::endl;
		}
		else {
			// Collision from the bottom side of the tile
			setPosition(sf::Vector2f(getLocation().x, tileBounds.top + tileBounds.height));
			std::cout << "Enemy collided at " << getLocation().x << getLocation().y << std::endl;
			std::cout << "Enemy direction " << getDirection().x << getDirection().y << std::endl;
		}
		// Reverse vertical direction
		m_direction.y = -m_direction.y;
	}
}


float Enemy::getSpeed() const
{
	return m_speed;
}

void Enemy::setSpeed(const float speed)
{
	m_speed = speed;
}

sf::Vector2f Enemy::getDirection() const
{
	return m_direction;
}

void Enemy::setDirection(const sf::Vector2f direction)
{
	m_direction = direction;
}