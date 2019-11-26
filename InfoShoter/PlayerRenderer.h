#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>
class PlayerRenderer
{
private:

	sf::Texture m_texture;

	// set up the animations for all four directions (set spritesheet and push frames)
	Animation m_walkingAnimationDown;
	Animation m_walkingAnimationLeft;
	Animation m_walkingAnimationRight;
	Animation m_walkingAnimationUp;
	Animation m_idleAnimation;
	Animation m_attackAnimationDown;
	Animation m_attackAnimationLeft;
	Animation m_attackAnimationRight;
	Animation m_attackAnimationUp;

	AnimatedSprite m_animatedSprite;
	Animation* m_currentAnimation;

public:

	PlayerRenderer(sf::Vector2f startPosition);
	~PlayerRenderer();
	void ChangeAnimation(int i);
	void PlayAnimation();
	// load texture (spritesheet)
	void Draw(sf::RenderWindow &window, sf::Time &frameTime);
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position_);
	void Move(sf::Vector2f movement, sf::Time &frameTime);
	
};

