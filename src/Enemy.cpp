	/*
	Enemy();
	~Enemy() override = default;

	virtual void move(sf::Time deltaTime) override;
	float getXVelocity();

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Tile& tile) override {};


	float m_speed = { 120.f };
	float m_directionX{ .2f };
	float m_directonY{ .2f };
	sf::Vector2f m_direction;
	*/
#include "Enemy.h"

Enemy::Enemy()
{
	m_shape = std::make_unique<sf::CircleShape>(tileSize / 2.0f);
	m_shape->setFillColor(sf::Color::Red);
	
}

void Enemy::move(sf::Time deltaTime)
{
	m_shape->move(m_direction * m_speed * deltaTime.asSeconds());
	setPosition(m_shape->getPosition());
}


void Enemy::reboundSides()
{
	m_direction.x -= m_direction.x;
}

void Enemy::reboundTopBottom()
{
	m_direction.y = -m_direction.y;
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