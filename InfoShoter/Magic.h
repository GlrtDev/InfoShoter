#pragma once
//#include "ParticleRenderer.h"
#include "Projectile.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <string>
#include <vector>
#include <TGUI/Widgets/Picture.hpp>
class Magic
{
	sf::Texture m_iconTexture;
	//sf::Texture m_icon;
	std::string m_name;
	std::vector<Projectile> m_projectiles;
	int m_damage;
	int m_speed;
	int m_manaCost;
	float m_rechargeTime; // in sec
	int m_type; // 0 fire , 1 ice , 2 wind
	Projectile* projectile;
	bool m_projectileLoaded;
	int m_playerMagicLevel;
public:
	Magic(int level, float seedAsFrameTimeSec, int playerMagicLevel);
	~Magic();
	bool ShotProjectile(const std::string lastFacingSide,sf::Vector2f startPosition);
	void DrawProjectiles(sf::RenderWindow & window, sf::Time & frameTime);
	std::string GetName();
	int GetDamage();
	int GetSpeed();
	int GetManaCost();
	float GetRechargeTime();
	int GetType();
	sf::Texture GetIconTexture();
	int CalculateRecharge(sf::Time & frameTime);
	std::vector<Projectile>* GetProjectiles();
	void LevelUp();
};

