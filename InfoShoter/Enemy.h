#pragma once
#include "EnemyRenderer.h"
#include <queue>
#include <SFML/Graphics.hpp>
class Enemy : public EnemyRenderer
{
protected:
	float velocity;
	std::queue<sf::Vector2f> path;
	sf::Vector2f currentCheckpoint, nextCheckpoint;
	bool alive;
public:
	Enemy(std::queue<sf::Vector2f> path_);
	~Enemy();
	bool Move(sf::Vector2f targetPosition, sf::Time &frameTime);
	void FollowPath(sf::Time &frameTime);

};

