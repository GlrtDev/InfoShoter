#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "TGUI/TGUI.hpp"
#include <iostream>
class EnemyRenderer
{
protected:
	sf::Texture texture;
	Animation walkingAnimationLeft;
	Animation walkingAnimationRight;

	AnimatedSprite animatedSprite;
	Animation* currentAnimation;

	sf::RectangleShape healthBar;
	sf::RectangleShape healthBarBackground;
	sf::Vector2i healthBarOffset;
	sf::CircleShape minimapDot;
	sf::Vector2f minimapOffset;

	sf::CircleShape boundingBoxDots[4];
public:
	EnemyRenderer();
	~EnemyRenderer();
	void Draw(sf::RenderWindow &window, sf::Time &frameTime);
	void DrawOnMinimap(sf::RenderWindow &window);
	sf::Vector2f GetPosition();
	void ChangeAnimation(int i);
};

