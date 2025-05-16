#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile();
	~Tile() override = default;
	//virtual void handleCollision(GameObject& unknownObj) = 0;
	Tile operator=(const Tile& other);
private:
};