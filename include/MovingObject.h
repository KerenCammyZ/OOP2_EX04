#pragma once
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	MovingObject();
	~MovingObject() override = default;
	virtual void move(sf::Time deltaTime) = 0;

private:

};