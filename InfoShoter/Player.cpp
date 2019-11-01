#include "player.h"
#include <cmath>

#define M_PI 3.14159265358979323846

Player::Player()
{
	maxSpeed = sf::Vector2f(150.f, 150.f);
	maxSpeedInv = sf::Vector2f(-150.f, -150.f);
}

void Player::Move(sf::Time &frameTime)
{
	if (velocity.x > maxSpeed.x)
		velocity.x -= .5f;
	if (velocity.x < maxSpeedInv.x)
		velocity.x += .5f;

	if (velocity.y > maxSpeed.y)
		velocity.y -= .5f;
	if (velocity.y < maxSpeedInv.y)
		velocity.y += .5f;

	velocity += acceleration;
	Renderer.Move(velocity, frameTime);
}

void Player::SetAcceleration(PlayerDirections direction)
{
	switch (direction)
	{
	case UP:
		Renderer.ChangeAnimation(0);
		if (velocity.y > 0)
			acceleration.y = -1.5f;
		else
		acceleration.y = -.5f;
		break;

	case DOWN:
		Renderer.ChangeAnimation(1);
		if (velocity.y < 0)
			acceleration.y = 1.5f;
		else
		acceleration.y = .5f;

		break;

	case RIGHT:
		Renderer.ChangeAnimation(2);
		if (velocity.x < 0)
			acceleration.x = 1.5f;
		else
		acceleration.x = .5f;
		break;

	case LEFT:
		Renderer.ChangeAnimation(3);
		if (velocity.x > 0)
			acceleration.x = -1.5f;
		else
		acceleration.x = -.5f;

		break;

	default:
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

void Player::Control()
{
	bool moveKeyPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		SetAcceleration(Player::PlayerDirections::UP);
		moveKeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		SetAcceleration(Player::PlayerDirections::DOWN);
		moveKeyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		SetAcceleration(Player::PlayerDirections::LEFT);
		moveKeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		SetAcceleration(Player::PlayerDirections::RIGHT);
		moveKeyPressed = true;
	}

	if (!moveKeyPressed)
		SetAcceleration(Player::PlayerDirections::IDLE);

	Renderer.PlayAnimation();
}

