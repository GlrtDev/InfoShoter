#pragma once
#include "gun.h"
#include <list>
#include <SFML/System/Vector2.hpp>

class Player
{
private:
	struct velocity
	{
		sf::Vector2f vector;
		float rotation;
	};

	struct acceleration
	{
		sf::Vector2f vector;
		float rotation;
	};

	struct position
	{
		sf::Vector2f vector;
		float rotation;
	};

	int gold;
	
	int score;

	std::list<Gun> Guns;

};