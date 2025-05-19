#pragma once
#include "MovingObject.h"

class Player : public MovingObject
{
public:
	Player();
	~Player() override = default;
	virtual void move(sf::Time deltaTime);

	//setters and getters
	void setDirection(sf::Keyboard::Key keyCode);
	//void setLife(int life);




private:
	//int m_life;
	sf::Vector2f m_direction;
	float m_speed = 160.f;
};