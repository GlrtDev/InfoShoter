#include "Projectile.h"



Projectile::Projectile(int damage, int speed, int type) : m_damage(damage), m_speed(speed), m_type(type)
{
	switch (type) {
	case 0:
		m_animatedSprite.setAnimation(m_fireballFly);
		break;
	case 1:
		m_animatedSprite.setAnimation(m_iceFly);
		break;
	case 2:
		m_animatedSprite.setAnimation(m_tornadoFly);
		break;
	}
	m_readyToDie = false;
}


Projectile::~Projectile()
{
}

void Projectile::Move(sf::Time & frameTime)
{
	static sf::Time lifeTime;
	if (m_facingSide == "UP") {
		m_animatedSprite.move(0,-m_speed * frameTime.asSeconds());
	}
	else if (m_facingSide == "DOWN") {
		m_animatedSprite.move(0, m_speed * frameTime.asSeconds());
	}
	else if (m_facingSide == "RIGHT") {
		m_animatedSprite.move(m_speed * frameTime.asSeconds(), 0);
	}
	else if (m_facingSide == "LEFT") {
		m_animatedSprite.move(-m_speed * frameTime.asSeconds(), 0);
	}
	lifeTime += frameTime;
	if (lifeTime.asSeconds() > 0.7f) {
		lifeTime = sf::Time::Zero;
		m_readyToDie = true;
	}
}

void Projectile::SetDirection(const std::string FacingSide, sf::Vector2f startPosition) {
	m_facingSide = FacingSide;
	m_animatedSprite.setPosition(startPosition);
	if (m_type != 2) {
		if (m_facingSide == "UP") {
			m_animatedSprite.setRotation(270.f);
			m_animatedSprite.setPosition(startPosition + sf::Vector2f(0, 50));
		}
		else if (m_facingSide == "DOWN") {
			m_animatedSprite.setRotation(90.f);
			m_animatedSprite.setPosition(startPosition + sf::Vector2f(61, 10));
		}
		else if (m_facingSide == "LEFT") {
			m_animatedSprite.setRotation(180.f);
			m_animatedSprite.setPosition(startPosition + sf::Vector2f(53, 61));
		}
		else if (m_facingSide == "RIGHT") {
			m_animatedSprite.setRotation(0.f);
			m_animatedSprite.setPosition(startPosition);
		}
	}
	else
		m_animatedSprite.setPosition(startPosition + sf::Vector2f(-20, -20));
	m_animatedSprite.play();
}

bool Projectile::CheckStatus()
{
	return m_readyToDie;
}
