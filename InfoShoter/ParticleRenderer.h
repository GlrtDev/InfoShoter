#pragma once
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>
#include "AnimatedSprite.hpp"

class ParticleRenderer
{
protected:
	sf::Texture m_textureFireball;
	sf::Texture m_textureTornado;
	sf::Texture m_textureIce;
	//Animation m_flyDown;
	//Animation m_flyLeft;
	Animation m_fireballFly;
	Animation m_iceFly;
	Animation m_tornadoFly;
	//Animation m_flyUp;

	AnimatedSprite m_animatedSprite;
	Animation* m_currentAnimation;

	//sf::CircleShape collisionPoint;
public:
	ParticleRenderer();
	~ParticleRenderer();
	//void SetDirection(const std::string lastFacingSide);
	void Draw(sf::RenderWindow &window, sf::Time &frameTime);
};

