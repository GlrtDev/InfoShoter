#pragma once
#include "ParticleRenderer.h"
class Projectile :
	public ParticleRenderer
{
	int m_damage;
	int m_speed;
	const std::string m_facingSide;
public:
	Projectile(int damage, int speed,int type, const std::string FacingSide, sf::Vector2f startPosition);
	~Projectile();
	void Move(sf::Time &frameTime);
};

