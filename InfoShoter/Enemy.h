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
	//bool alive;
public:
	std::vector<sf::Vector2f> GetboundingBox();
	Enemy(std::queue<sf::Vector2f> path_);
	~Enemy();
	bool Move(sf::Vector2f targetPosition, sf::Time &frameTime);
	void FollowPath(sf::Time &frameTime);
	sf::Vector2f getPosition();

	bool ReceiveDamage(int damage);

	void KillThis();

};

