#pragma once
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"

class EmptyTile : public Tile
{
	public:
	EmptyTile() : Tile() {}
	~EmptyTile() override = default;
	
	virtual void handleCollision(GameObject* otherObj) override {} // Empty tile does not handle collisions with other objects
};