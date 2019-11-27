#include "player.h"
//#include <cmath>

//#define M_PI 3.14159265358979323846

Player::Player(sf::Vector2f startPosition) : m_boundingBox({ { sf::Vector2f(-35.f, -25.f), sf::Vector2f(-21.f, -25.f), sf::Vector2f(-35.f, -50.f), sf::Vector2f(-21.f, -50.f), sf::Vector2f(-21.f, 0.f), sf::Vector2f(-35.f, 0.f) } }), Renderer(startPosition), m_expNeededToLevelUp(100)
{
	maxSpeed = sf::Vector2f(150.f, 150.f);
	maxSpeedInv = sf::Vector2f(-150.f, -150.f);
	m_swordDamage = 5;
	m_level = 1;
	m_exp = 0;
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

void Player::SetAcceleration(PlayerStates direction, bool m_isAttacking, const std::string facingSide)
{
	float speed = 1.5f;
	switch (direction)
	{
	case UP:
		if (m_isAttacking) {
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
		if (m_isAttacking) {
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
		if (m_isAttacking) {
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
		if (m_isAttacking) {
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
		if (m_isAttacking) 
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
	m_isAttacking = false;
	bool KeyPressed = false;
	static std::string facingSide;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		m_isAttacking = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		facingSide = "UP";
		SetAcceleration(Player::PlayerStates::UP,m_isAttacking,facingSide);
		KeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		facingSide = "DOWN";
		SetAcceleration(Player::PlayerStates::DOWN,m_isAttacking, facingSide);
		KeyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		facingSide = "LEFT";
		SetAcceleration(Player::PlayerStates::LEFT, m_isAttacking, facingSide);
		KeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		facingSide = "RIGHT";
		SetAcceleration(Player::PlayerStates::RIGHT, m_isAttacking, facingSide);
		KeyPressed = true;
	}
	

	if (!KeyPressed)
		SetAcceleration(Player::PlayerStates::IDLE, m_isAttacking, facingSide);

	Renderer.PlayAnimation();
}

int Player::GetDamage()
{
	return m_swordDamage;
}

bool Player::IsAttacking()
{
	return m_isAttacking;
}

int Player::GetLevel()
{
	return m_level;
}

void Player::GainExp(int experience)
{
	m_exp += experience;
	if (m_exp >= m_expNeededToLevelUp * m_level)
		LevelUp();
}

void Player::LevelUp()
{
	m_level += 1;
	m_exp = 0;
}

int Player::GetExpPercentage()
{
	return (100 * m_exp) / (m_expNeededToLevelUp * m_level); // 100 at front stands for 100%
}

