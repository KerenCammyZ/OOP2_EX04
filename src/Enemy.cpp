#include "Enemy.h"
#include <FullTile.h>

Enemy::Enemy()
{
	m_shape = std::make_unique<sf::CircleShape>(tileSize / 2.0f);
    m_shape->setFillColor(sf::Color::Red);
	m_shape->setOrigin(tileSize / 2.0f, tileSize / 2.0f);


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


void Enemy::handleCollision(Tile& tile)
{

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