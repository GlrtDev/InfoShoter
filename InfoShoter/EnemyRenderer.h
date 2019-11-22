#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>
class EnemyRenderer
{
protected:
	sf::Texture texture;
	Animation walkingAnimationLeft;
	Animation walkingAnimationRight;

	AnimatedSprite animatedSprite;
	Animation* currentAnimation;
public:
	EnemyRenderer();
	~EnemyRenderer();
	void Draw(sf::RenderWindow &window, sf::Time &frameTime);
	sf::Vector2f GetPosition();
	void ChangeAnimation(int i);
};

