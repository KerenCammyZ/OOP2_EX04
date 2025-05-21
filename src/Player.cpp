#include "Player.h"
#include "MovingObject.h"

Player::Player()
{
	m_shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(tileSize, tileSize));
	setColor(sf::Color::Magenta);
	setPosition(sf::Vector2f(0, 0));
}

void Player::setDirection(sf::Keyboard::Key keyCode)
{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		{
			m_direction = sf::Vector2f(0, -1);
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
		{
			m_direction = sf::Vector2f(0, 1);
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		{
			m_direction = sf::Vector2f(-1, 0);
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		{
			m_direction = sf::Vector2f(1, 0);
		}
		else
		{
			m_direction = sf::Vector2f(0, 0);
		}
}

//void Player::removeLife()
//{
//	m_life--;
//}
//
//int Player::getLife()
//{
//	return m_life;
//}

void Player::move(sf::Time deltaTime)
{
	m_oldPosition = m_shape->getPosition();
	m_shape->move(m_direction * m_speed * deltaTime.asSeconds());
	setPosition(m_shape->getPosition());
}
