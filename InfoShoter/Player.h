#pragma once
#include "gun.h"
#include <list>
#include <SFML/System/Vector2.hpp>
#include "PlayerRenderer.h"

class Player
{
private:
	sf::Vector2f velocity; //sped
	sf::Vector2f acceleration;
	sf::Vector2f maxSpeed, maxSpeedInv;
	int gold;
	int score;

	std::list<Gun> Guns;

public:
	enum PlayerDirections { UP, DOWN, RIGHT, LEFT, IDLE };
	Player();
	PlayerRenderer Renderer;
	void Move(sf::Time &frameTime);
	void SetAcceleration(PlayerDirections direction);
	void ResetVelocityX();
	void ResetVelocityY();

	void Control();
};