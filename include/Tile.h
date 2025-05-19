#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile();
	~Tile() override = default;
	Tile operator=(const Tile& other);
	//virtual void handleCollision(GameObject& unknownObj) = 0;

private:
};