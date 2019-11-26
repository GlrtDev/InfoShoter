#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include "TGUI/TGUI.hpp"
#include <iostream>
class EnemyRenderer
{
protected:
	sf::Texture m_texture;
	Animation m_walkingAnimationLeft;
	Animation m_walkingAnimationRight;

	AnimatedSprite m_animatedSprite;
	Animation* m_currentAnimation;

	sf::RectangleShape m_healthBar;
	sf::RectangleShape m_healthBarBackground;
	sf::Vector2i m_healthBarOffset;
	sf::CircleShape m_minimapDot;
	sf::Vector2f m_minimapOffset;

	sf::CircleShape m_boundingBoxDots[4];

	//bool dead;
public:
	EnemyRenderer();
	~EnemyRenderer();
	void Draw(sf::RenderWindow &window, sf::Time &frameTime);
	void DrawOnMinimap(sf::RenderWindow &window);
	sf::Vector2f GetPosition();
	void ChangeAnimation(int i);
};

