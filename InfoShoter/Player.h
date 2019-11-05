#pragma once
#include "gun.h"
#include <list>
#include <SFML/System/Vector2.hpp>
#include "PlayerRenderer.h"
#include <array>

class Player
{
private:
	sf::Vector2f velocity; //sped
	sf::Vector2f acceleration;
	sf::Vector2f maxSpeed, maxSpeedInv;
	int gold;
	int score;
	
	std::list<Gun> Guns;
	//sf::Vector2f startPosition;
public:
	std::array<sf::Vector2f, 4> boundingBox;

	enum PlayerDirections { UP, DOWN, RIGHT, LEFT, IDLE };
	Player(sf::Vector2f startPosition);
	PlayerRenderer Renderer;
	void Move(sf::Time &frameTime);
	void SetAcceleration(PlayerDirections direction);
	void ResetVelocityX();
	void ResetVelocityY();
	void WallCollision(sf::Time &frameTime);
	void Control();
};