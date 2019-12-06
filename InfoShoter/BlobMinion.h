#pragma once
#include "Enemy.h"
class BlobMinion :
	public Enemy
{
public:
	BlobMinion(std::queue<sf::Vector2f> path_, int level_);
	~BlobMinion();
};

