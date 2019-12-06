#pragma once
#include "Enemy.h"
class Goblin :
	public Enemy
{
public:
	Goblin(std::queue<sf::Vector2f> path_, int level_);
	~Goblin();
};

