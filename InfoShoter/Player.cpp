#include "player.h"
//#include <cmath>

//#define M_PI 3.14159265358979323846

Player::Player(sf::Vector2f startPosition) : boundingBox({ { sf::Vector2f(-35.f, -25.f), sf::Vector2f(-21.f, -25.f), sf::Vector2f(-35.f, -50.f), sf::Vector2f(-21.f, -50.f), sf::Vector2f(-21.f, 0.f), sf::Vector2f(-35.f, 0.f) } }), Renderer(startPosition)
{
	maxSpeed = sf::Vector2f(150.f, 150.f);
	maxSpeedInv = sf::Vector2f(-150.f, -150.f);
	swordDamage = 5;

}

void Player::Move(sf::Time &frameTime)
{
	if (velocity.x > maxSpeed.x)
		velocity.x -= 1.5f;
	if (velocity.x < maxSpeedInv.x)
		velocity.x += 1.5f;

	if (velocity.y > maxSpeed.y)
		velocity.y -= 1.5f;
	if (velocity.y < maxSpeedInv.y)
		velocity.y += 1.5f;

	velocity += acceleration;
	Renderer.Move(velocity, frameTime);
}

void Player::SetAcceleration(PlayerStates direction, bool attack, const std::string facingSide)
{
	float speed = 1.5f;
	switch (direction)
	{
	case UP:
		if (attack) {
			Renderer.ChangeAnimation(5);
			speed = 1.f;
		}
		else
			Renderer.ChangeAnimation(0);
		if (velocity.y > 0)
			acceleration.y = -2.5f;
		else
			acceleration.y = -speed;
		break;

	case DOWN:
		if (attack) {
		Renderer.ChangeAnimation(6);
		speed = 1.f;
		}
		else
			Renderer.ChangeAnimation(1);
		if (velocity.y < 0)
			acceleration.y = 2.5f;
		else
		acceleration.y = speed;

		break;

	case RIGHT:
		if (attack) {
			Renderer.ChangeAnimation(7);
			speed = 1.f;
		}
		else
			Renderer.ChangeAnimation(2);
		if (velocity.x < 0)
			acceleration.x = 2.5f;
		else
		acceleration.x = speed;
		break;

	case LEFT:
		if (attack) {
			Renderer.ChangeAnimation(8);
			speed = 1.f;
		}
		else
			Renderer.ChangeAnimation(3);
		if (velocity.x > 0)
			acceleration.x = -2.5f;
		else
		acceleration.x = -speed;

		break;

	default:
		if (attack) 
		{
			if (facingSide == "LEFT")
				Renderer.ChangeAnimation(8);
			else if (facingSide == "RIGHT")
				Renderer.ChangeAnimation(7);
			else if (facingSide == "UP")
				Renderer.ChangeAnimation(5);
			else
				Renderer.ChangeAnimation(6);
		}
		else
			Renderer.ChangeAnimation(4);
		acceleration.x = 0.f;
		acceleration.y = 0.f;

		if (velocity.x != 0)
		{
			velocity.x -= (velocity.x) / 100.f;	
			
		}
		
		if (velocity.y != 0)
		{
			velocity.y -= (velocity.y) / 100.f;
		}
		break;

	}
	
}

void Player::ResetVelocityX()
{
	velocity.x = 0;
	acceleration.x = 0;
}
void Player::ResetVelocityY()
{
	velocity.y = 0;
	acceleration.y = 0;
}

void Player::WallCollision(sf::Time &frameTime)
{
	Renderer.Move(-velocity, frameTime);
}

void Player::Control()
{
	swordDamage = 0;
	bool attack = false;
	bool KeyPressed = false;
	static std::string facingSide;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		attack = true;
		swordDamage = 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		facingSide = "UP";
		SetAcceleration(Player::PlayerStates::UP,attack,facingSide);
		KeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		facingSide = "DOWN";
		SetAcceleration(Player::PlayerStates::DOWN,attack, facingSide);
		KeyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		facingSide = "LEFT";
		SetAcceleration(Player::PlayerStates::LEFT, attack, facingSide);
		KeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		facingSide = "RIGHT";
		SetAcceleration(Player::PlayerStates::RIGHT, attack, facingSide);
		KeyPressed = true;
	}
	

	if (!KeyPressed)
		SetAcceleration(Player::PlayerStates::IDLE, attack, facingSide);

	Renderer.PlayAnimation();
}

int Player::GetDamage()
{
	return swordDamage;
}

