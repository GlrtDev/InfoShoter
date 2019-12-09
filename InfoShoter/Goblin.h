#pragma once
#include "Enemy.h"
class Goblin :
	public Enemy
{
public:
	Goblin(const std::queue<sf::Vector2f> path_, int level_);
	~Goblin();
};

