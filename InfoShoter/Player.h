#pragma once
#include "gun.h"
#include <list>
#include <SFML/System/Vector2.hpp>
#include "PlayerRenderer.h"
#include <array>
#include <string>

class Player
{
private:
	sf::Vector2f m_velocity; //sped
	sf::Vector2f acceleration;
	sf::Vector2f maxSpeed, maxSpeedInv;
	int gold;
	int score;
	int swordDamage;
	std::list<Gun> Guns;

public:
	std::array<sf::Vector2f, 6> m_boundingBox;

	enum PlayerStates { UP, DOWN, RIGHT, LEFT, IDLE };
	Player(sf::Vector2f startPosition);
	PlayerRenderer Renderer;
	void Move(sf::Time &frameTime);
	void SetAcceleration(PlayerStates direction, bool attack, const std::string facingSide);
	void Resetm_velocityX();
	void Resetm_velocityY();
	void WallCollision(sf::Time &frameTime);
	void Control();
	int GetDamage();
};