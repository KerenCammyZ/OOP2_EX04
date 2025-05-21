#pragma once  
#include "MovingObject.h"  

class Enemy : public MovingObject  
{  
public:  
   Enemy();  
   ~Enemy() = default; 

   virtual void move(sf::Time deltaTime) override;

	virtual void handleCollision(GameObject& unknownObj) override {};
	virtual void handleCollision(Enemy& enemy) override {};
	virtual void handleCollision(Player& player) override {};
	virtual void handleCollision(Tile& tile) override {};

private:
	// m_shape
};
