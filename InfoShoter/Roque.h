#pragma once
#include "Enemy.h"
class Roque :
	public Enemy
{
public:
	Roque(const std::queue<sf::Vector2f> path_, int level_);
	~Roque();
};

