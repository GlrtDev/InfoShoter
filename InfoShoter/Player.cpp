#include "player.h"
//#include <cmath>

//#define M_PI 3.14159265358979323846

Player::Player(sf::Vector2f startPosition) : m_boundingBox({ { sf::Vector2f(-35.f, -25.f), sf::Vector2f(-21.f, -25.f), sf::Vector2f(-35.f, -50.f), sf::Vector2f(-21.f, -50.f), sf::Vector2f(-21.f, 0.f), sf::Vector2f(-35.f, 0.f) } }), Renderer(startPosition)
{
	maxSpeed = sf::Vector2f(150.f, 150.f);
	maxSpeedInv = sf::Vector2f(-150.f, -150.f);
	swordDamage = 5;

}

void Player::Move(sf::Time &frameTime)
{
	if (m_velocity.x > maxSpeed.x)
		m_velocity.x -= 1.5f;
	if (m_velocity.x < maxSpeedInv.x)
		m_velocity.x += 1.5f;

	if (m_velocity.y > maxSpeed.y)
		m_velocity.y -= 1.5f;
	if (m_velocity.y < maxSpeedInv.y)
		m_velocity.y += 1.5f;

	m_velocity += acceleration;
	Renderer.Move(m_velocity, frameTime);
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
		if (m_velocity.y > 0)
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
		if (m_velocity.y < 0)
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
		if (m_velocity.x < 0)
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
		if (m_velocity.x > 0)
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

		if (m_velocity.x != 0)
		{
			m_velocity.x -= (m_velocity.x) / 100.f;	
			
		}
		
		if (m_velocity.y != 0)
		{
			m_velocity.y -= (m_velocity.y) / 100.f;
		}
		break;

	}
	
}

void Player::Resetm_velocityX()
{
	m_velocity.x = 0;
	acceleration.x = 0;
}
void Player::Resetm_velocityY()
{
	m_velocity.y = 0;
	acceleration.y = 0;
}

void Player::WallCollision(sf::Time &frameTime)
{
	Renderer.Move(-m_velocity, frameTime);
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

