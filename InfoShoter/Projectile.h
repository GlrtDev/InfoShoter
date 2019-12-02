#pragma once
#include "ParticleRenderer.h"
class Projectile :
	public ParticleRenderer
{
	int m_damage;
	int m_speed;
	int m_type;
	std::string m_facingSide;
	bool m_readyToDie;
public:
	Projectile(int damage, int speed,int type);
	~Projectile();
	void Move(sf::Time &frameTime);
	void SetDirection(const std::string FacingSide, sf::Vector2f startPosition);
	bool CheckStatus();
};

