#pragma once
#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	StaticObject();
	~StaticObject() override = default;
	virtual void handleCollision(GameObject& unknownObj) = 0;
private:
};