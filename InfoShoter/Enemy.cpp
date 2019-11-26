#include "Enemy.h"
#include <math.h>


std::vector<sf::Vector2f> Enemy::GetboundingBox()
{
	return m_boundingBox;
}

Enemy::Enemy(std::queue<sf::Vector2f> path_) : m_path(path_)
{
	
}


Enemy::~Enemy()
{
}

bool Enemy::Move(sf::Vector2f targetPosition, sf::Time &frameTime) {
	
	bool targetReached = false;
	sf::Vector2f delta,movement;
	delta.x = targetPosition.x - m_animatedSprite.getPosition().x;
	delta.y = targetPosition.y - m_animatedSprite.getPosition().y;
	int side = (delta.x > 0) ? 1 : ( (delta.x < 0 ) ? -1 : 0 );

	float movex = 0.f, movey = 0.f;
	if (fabs(delta.x) > fabs(delta.y)) { //move horizontally

		movex = m_velocity * side;
		ChangeAnimation(side);
		if (fabs(delta.x) <= 1.f) {
			m_animatedSprite.setPosition(targetPosition);
			targetReached = true;
		}
	}
	else { //move vertically
		movey = m_velocity * ((delta.y > 0) ? 1 : -1);
		if (fabs(delta.y) <= 1.f) {
			m_animatedSprite.setPosition(targetPosition);
			targetReached = true;
		}
	}
	//std::cout << std::endl << "y " << delta.y << " y mov  " << movey << " x " << delta.x << " y mov  " << movex;
	//std::cout << std::endl << "x " << animatedSprite.getPosition().x << " y  " << animatedSprite.getPosition().y << " tar" << targetPosition.x << " " << targetPosition.y;
	movement = sf::Vector2f(movex, movey);
	m_animatedSprite.move(movement * frameTime.asSeconds());
	m_healthBar.setPosition(m_animatedSprite.getPosition().x + m_healthBarOffset.x, m_animatedSprite.getPosition().y + m_healthBarOffset.y);
	m_healthBarBackground.setPosition(m_animatedSprite.getPosition().x + m_healthBarOffset.x, m_animatedSprite.getPosition().y + m_healthBarOffset.y);
	for (int i = 0; i < 4; i++) 
		m_boundingBoxDots[i].setPosition(m_animatedSprite.getPosition() + m_boundingBox[i]);
	return targetReached;
}

void Enemy::FollowPath(sf::Time &frameTime)
{
	if (!m_path.empty()) {
		if (Move(m_path.front(), frameTime)) {
			m_path.pop();
			//std::cout << "POOOOOOOOP";
		}
		
	}
	else {
		//std::cout << "nie" << std::endl;
	}
}

sf::Vector2f Enemy::getPosition()
{
	return m_animatedSprite.getPosition();
}

bool Enemy::ReceiveDamage(int damage)
{
	m_healthPoints -= damage;
	m_healthBar.setSize(sf::Vector2f(25.f*((float)m_healthPoints /(float) m_maxHealthPoints), 4.f));
	std::cout << m_healthPoints << std::endl;
	if (m_healthPoints <= 0) {
		KillThis();
		//m_animatedSprite.pause();
		//dead = true;
		return true;
	}
	return false;
}

void Enemy::KillThis()
{
	//delete this;
	//dead = true;
}
