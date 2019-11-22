#pragma once
#include "EnemyRenderer.h"
#include <queue>
#include <array>
#include <SFML/Graphics.hpp>
class Enemy : public EnemyRenderer
{
protected:
	float velocity;
	std::queue<sf::Vector2f> path;
	sf::Vector2f currentCheckpoint, nextCheckpoint;
	int healthPoints;
	int maxHealthPoints;
	bool alive;
public:
	std::vector<sf::Vector2f> boundingBox;
	Enemy(std::queue<sf::Vector2f> path_);
	~Enemy();
	bool Move(sf::Vector2f targetPosition, sf::Time &frameTime);
	void FollowPath(sf::Time &frameTime);
	sf::Vector2f getPosition();

	bool ReceiveDamage(int damage);

	void KillThis();

};

