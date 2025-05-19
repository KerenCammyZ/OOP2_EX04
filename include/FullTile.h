#pragma once
#include "Tile.h"
#include "Player.h"
#include "Enemy.h"

class FullTile : public Tile 
{
public:
	FullTile();
	~FullTile() override = default;

	// handleCollision(GameObject* unknownObject) override;
	// handleCollision(Player* player) override;
	// handleCollision(Enemy* enemy) override;

private:

};