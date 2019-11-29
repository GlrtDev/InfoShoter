#include "Projectile.h"



Projectile::Projectile(int damage, int speed, int type, const std::string FacingSide, sf::Vector2f startPosition) : m_damage(damage), m_speed(speed), m_facingSide(FacingSide)
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
	m_animatedSprite.setPosition(startPosition);
	if (type != 2) {
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
	}
	else
		m_animatedSprite.setPosition(startPosition + sf::Vector2f(-20, -20));
	m_animatedSprite.play();
}


Projectile::~Projectile()
{
}

void Projectile::Move(sf::Time & frameTime)
{
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
}
