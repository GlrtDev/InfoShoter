#pragma once
#include "Enemy.h"
class Knight :
	public Enemy
{
public:
	Knight(std::queue<sf::Vector2f> path_, int level_);
	~Knight();
};

