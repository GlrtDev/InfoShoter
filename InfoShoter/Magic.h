#pragma once
//#include "ParticleRenderer.h"
#include "Projectile.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include <vector>
class Magic
{
	sf::Sprite m_icon;
	std::string m_name;
	std::vector<Projectile> m_projectiles;
	int m_damage;
	int m_speed;
	int m_manaCost;
	float m_rechargeTime;
	int m_type; // 0 fire , 1 ice , 2 wind
public:
	Magic(int level);
	~Magic();
	void ShotProjectile(const std::string lastFacingSide,sf::Vector2f startPosition);
	void DrawProjectiles(sf::RenderWindow & window, sf::Time & frameTime);

};

