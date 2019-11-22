#include "Enemy.h"
#include <math.h>


Enemy::Enemy(std::queue<sf::Vector2f> path_) : path(path_)
{
}


Enemy::~Enemy()
{
}

bool Enemy::Move(sf::Vector2f targetPosition, sf::Time &frameTime) {
	
	bool targetReached = false;
	sf::Vector2f delta,movement;
	delta.x = targetPosition.x - animatedSprite.getPosition().x;
	delta.y = targetPosition.y - animatedSprite.getPosition().y;
	int side = (delta.x > 0) ? 1 : ( (delta.x < 0 ) ? -1 : 0 );

	float movex = 0.f, movey = 0.f;
	if (fabs(delta.x) > fabs(delta.y)) { //move horizontally

		movex = velocity * side;
		ChangeAnimation(side);
		if (fabs(delta.x) <= 1.f) {
			animatedSprite.setPosition(targetPosition);
			targetReached = true;
		}
	}
	else { //move vertically
		movey = velocity * ((delta.y > 0) ? 1 : -1);
		if (fabs(delta.y) <= 1.f) {
			animatedSprite.setPosition(targetPosition);
			targetReached = true;
		}
	}
	//std::cout << std::endl << "y " << delta.y << " y mov  " << movey << " x " << delta.x << " y mov  " << movex;
	//std::cout << std::endl << "x " << animatedSprite.getPosition().x << " y  " << animatedSprite.getPosition().y << " tar" << targetPosition.x << " " << targetPosition.y;
	movement = sf::Vector2f(movex, movey);
	animatedSprite.move(movement * frameTime.asSeconds());
	healthBar.setPosition(animatedSprite.getPosition().x + healthBarOffset.x, animatedSprite.getPosition().y + healthBarOffset.y);
	healthBarBackground.setPosition(animatedSprite.getPosition().x + healthBarOffset.x, animatedSprite.getPosition().y + healthBarOffset.y);
	for (int i = 0; i < 4; i++) 
		boundingBoxDots[i].setPosition(animatedSprite.getPosition() + boundingBox[i]);
	return targetReached;
}

void Enemy::FollowPath(sf::Time &frameTime)
{
	if (!path.empty()) {
		if (Move(path.front(), frameTime)) {
			path.pop();
			//std::cout << "POOOOOOOOP";
		}
		
	}
	else {
		std::cout << "nie" << std::endl;
	}
}

sf::Vector2f Enemy::getPosition()
{
	return animatedSprite.getPosition();
}

bool Enemy::ReceiveDamage(int damage)
{
	healthPoints -= damage;
	healthBar.setSize(sf::Vector2f(25.f*((float)healthPoints /(float) maxHealthPoints), 4.f));
	std::cout << healthPoints << std::endl;
	if (healthPoints <= 0) {
		KillThis();
		return true;
	}
	return false;
}

void Enemy::KillThis()
{
	//delete this;
}
