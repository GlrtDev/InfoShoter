#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>
class PlayerRenderer
{
private:

	sf::Texture texture;

	// set up the animations for all four directions (set spritesheet and push frames)
	Animation walkingAnimationDown;
	Animation walkingAnimationLeft;
	Animation walkingAnimationRight;
	Animation walkingAnimationUp;
	Animation idleAnimation;
	Animation attackAnimationDown;
	Animation attackAnimationLeft;
	Animation attackAnimationRight;
	Animation attackAnimationUp;

	AnimatedSprite animatedSprite;
	Animation* currentAnimation;

public:

	PlayerRenderer();
	~PlayerRenderer();
	void ChangeAnimation(int i);
	void PlayAnimation();
	// load texture (spritesheet)
	void Draw(sf::RenderWindow &window, sf::Time &frameTime);
	sf::Vector2f GetPosition();
	void Move(sf::Vector2f movement, sf::Time &frameTime);
	
};

