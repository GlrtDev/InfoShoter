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
	sf::Vector2f m_acceleration;
	sf::Vector2f m_maxSpeed, m_maxSpeedInv;
	//int gold;
	//int score;
	int m_level;
	int m_swordDamage;
	std::list<Gun> Guns; //TO DO
	bool m_isAttacking;
	const int m_expNeededToLevelUp;
	int m_exp;
	float m_speed;
	int m_skillpoints;
	int m_magicPower;
public:
	std::array<sf::Vector2f, 6> m_boundingBox;

	enum PlayerStates { UP, DOWN, RIGHT, LEFT, IDLE };
	Player(sf::Vector2f startPosition);
	PlayerRenderer Renderer;
	void Move(sf::Time &frameTime);
	void SetAcceleration(PlayerStates direction, bool m_isAttacking, const std::string facingSide);
	void Resetm_velocityX();
	void Resetm_velocityY();
	void WallCollision(sf::Time &frameTime);
	void Control();
	int GetDamage();
	bool IsAttacking();
	int GetLevel();
	void GainExp(int experience);
	void LevelUp();
	int GetExpPercentage();
	int GetSpeed();
	int GetSkillpoints();
	void AssignSkillpoints();
	int GetMagicPower();
};