#pragma once
#include "gun.h"
#include <list>

class Player
{
private:
	struct velocity
	{
		vector2
			rotation
	};

	struct acceleration
	{
		vector2
			rotation
	};

	struct position
	{
		vector2
			rotation
	};

	int gold;
	
	int score;

	std::list<Gun> Guns;

};