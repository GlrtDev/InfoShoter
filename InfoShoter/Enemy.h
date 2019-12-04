#pragma once
#include "EnemyRenderer.h"
#include <queue>
#include <array>
#include <SFML/Graphics.hpp>
class Enemy : public EnemyRenderer
{
protected:
	float m_velocity;
	std::queue<sf::Vector2f> m_path;
	//sf::Vector2f currentCheckpoint, nextCheckpoint;
	int m_healthPoints;
	int m_maxHealthPoints;
	std::vector<sf::Vector2f> m_boundingBox;
	int m_level;
	int m_healthLevelMultipler;
	int m_baseHealth;
	int m_exp;
	int m_baseExp;
	int m_expMultipler;
	//bool alive;
public:
	
	Enemy(std::queue<sf::Vector2f> path_,int level_);
	~Enemy();

	bool Move(sf::Vector2f targetPosition, sf::Time &frameTime);
	void FollowPath(sf::Time &frameTime);
	sf::Vector2f getPosition();
	std::vector<sf::Vector2f> GetboundingBox();

	bool ReceiveDamage(int damage);
	void KillThis();

	void InitializeEnemy();
	int GetExp();

	int GetLevel();
};

