#pragma once
#include "Enemy.h"
class BlobSlime :
	public Enemy
{
public:
	BlobSlime(std::queue<sf::Vector2f> path_, int level_);
	~BlobSlime();
	void Draw(sf::RenderWindow &window, sf::Time &frameTime) override;
};

