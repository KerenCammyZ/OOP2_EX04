#pragma once
#include "Tile.h"

class EmptyTile : public Tile
{
	public:
	EmptyTile();
	~EmptyTile() override = default;
	
	//virtual void handleCollision(GameObject* otherObj) override {} // Empty tile does not handle collisions with other objects
};