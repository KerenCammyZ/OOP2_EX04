#pragma once  
#include "MovingObject.h"  

class Enemy : public MovingObject  
{  
public:  
   Enemy();  
   ~Enemy() override = default;  

   void move(sf::Time deltaTime) override; // Implement pure virtual function  

private:  
   // m_shape  
};
