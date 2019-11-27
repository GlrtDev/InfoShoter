#pragma once
#include "Enemy.h"
class Bat : public Enemy {

public:
	Bat(std::queue<sf::Vector2f> path_, int level_);
};