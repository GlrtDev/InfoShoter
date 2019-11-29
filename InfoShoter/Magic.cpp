#include "Magic.h"
#include <random>


Magic::Magic(int level)
{
	std::minstd_rand0 randomNumberGenerator;
	std::uniform_int_distribution<int> randRange(50, 100);
	//randRange(randomNumberGenerator);
	randomNumberGenerator.seed(level);
	m_damage = level * randRange(randomNumberGenerator);
	m_speed = randRange(randomNumberGenerator);
	m_manaCost = m_damage + m_speed;
	m_rechargeTime = m_speed;
	m_type = randRange(randomNumberGenerator) % 3; // change to %3 later
	//m_currentAnimation = &m_walkingAnimationLeft;
	//m_animatedSprite.play(*m_currentAnimation);
}


Magic::~Magic()
{
}

void Magic::ShotProjectile(const std::string lastFacingSide, sf::Vector2f startPosition)
{
	Projectile* projectile = new Projectile(m_damage, m_speed, m_type, lastFacingSide,startPosition);
	m_projectiles.push_back(*projectile);
}

void Magic::DrawProjectiles(sf::RenderWindow & window, sf::Time & frameTime)
{
	for (auto& projectile : m_projectiles) {
		projectile.Move(frameTime);
		projectile.Draw(window, frameTime);
	}
}
