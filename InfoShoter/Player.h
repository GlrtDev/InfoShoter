#pragma once
#include "gun.h"
#include <list>
#include <SFML/System/Vector2.hpp>

class Player
{
private:
	sf::Vector2f velocity; //sped
	sf::Vector2f acceleration;
	sf::Vector2f position;

	int gold;
	int score;

	std::list<Gun> Guns;

public:

};