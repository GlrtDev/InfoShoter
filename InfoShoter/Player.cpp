#include "player.h"
//#include <cmath>

//#define M_PI 3.14159265358979323846

Player::Player(sf::Vector2f startPosition) : m_boundingBox({ { sf::Vector2f(-35.f, -25.f), sf::Vector2f(-21.f, -25.f), sf::Vector2f(-35.f, -50.f), sf::Vector2f(-21.f, -50.f), sf::Vector2f(-21.f, 0.f), sf::Vector2f(-35.f, 0.f) } }), Renderer(startPosition), m_expNeededToLevelUp(100)
{
	m_speed = 2;
	m_maxSpeed = sf::Vector2f(50.f * m_speed, 50.f * m_speed);
	m_maxSpeedInv = sf::Vector2f(-50.f * m_speed, -50.f * m_speed);
	m_swordDamage = 5;
	m_level = 1;
	m_exp = 0;
	m_skillpoints = 0;
	m_magicPower = 0;
	m_currentMagic = new Magic(1);
}

void Player::Move(sf::Time &frameTime)
{
	if (m_velocity.x > m_maxSpeed.x)
		m_velocity.x -= m_acceleration.x;
	if (m_velocity.x < m_maxSpeedInv.x)
		m_velocity.x -= m_acceleration.x;

	if (m_velocity.y > m_maxSpeed.y)
		m_velocity.y -= m_acceleration.y;
	if (m_velocity.y < m_maxSpeedInv.y)
		m_velocity.y -= m_acceleration.y;

	m_velocity += m_acceleration;
	Renderer.Move(m_velocity, frameTime);
}

void Player::SetAcceleration(PlayerStates direction, bool isAttacking, const std::string lastFacingSide)
{
	float speed = m_speed;
	switch (direction)
	{
	case UP:
		if (isAttacking) {
			Renderer.ChangeAnimation(5);
			speed /= 2.f; //slower when attackin
		}
		else
			Renderer.ChangeAnimation(0);
		if (m_velocity.y > 0)
			m_acceleration.y = -speed*1.5f; //quicker when turnin
		else
			m_acceleration.y = -speed;
		break;

	case DOWN:
		if (isAttacking) {
		Renderer.ChangeAnimation(6);
		speed /= 2.f;
		}
		else
			Renderer.ChangeAnimation(1);
		if (m_velocity.y < 0)
			m_acceleration.y = speed * 1.5f;
		else
		m_acceleration.y = speed;

		break;

	case RIGHT:
		if (isAttacking) {
			Renderer.ChangeAnimation(7);
			speed /= 2.f;
		}
		else
			Renderer.ChangeAnimation(2);
		if (m_velocity.x < 0)
			m_acceleration.x = speed * 1.5f;
		else
		m_acceleration.x = speed;
		break;

	case LEFT:
		if (isAttacking) {
			Renderer.ChangeAnimation(8);
			speed /= 2.f;
		}
		else
			Renderer.ChangeAnimation(3);
		if (m_velocity.x > 0)
			m_acceleration.x = -speed * 1.5f;
		else
		m_acceleration.x = -speed;

		break;

	default:
		if (isAttacking) 
		{
			if (lastFacingSide == "LEFT")
				Renderer.ChangeAnimation(8);
			else if (lastFacingSide == "RIGHT")
				Renderer.ChangeAnimation(7);
			else if (lastFacingSide == "UP")
				Renderer.ChangeAnimation(5);
			else
				Renderer.ChangeAnimation(6);
		}
		else
			Renderer.ChangeAnimation(4);
		m_acceleration.x = 0.f;
		m_acceleration.y = 0.f;

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
	m_acceleration.x = 0;
}
void Player::Resetm_velocityY()
{
	m_velocity.y = 0;
	m_acceleration.y = 0;
}

void Player::WallCollision(sf::Time &frameTime)
{
	Renderer.Move(-m_velocity, frameTime);
}

void Player::Control()
{
	m_isAttacking = false;
	bool KeyPressed = false;
	static std::string lastFacingSide;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		m_isAttacking = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		lastFacingSide = "UP";
		SetAcceleration(Player::PlayerStates::UP,m_isAttacking,lastFacingSide);
		KeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		lastFacingSide = "DOWN";
		SetAcceleration(Player::PlayerStates::DOWN,m_isAttacking, lastFacingSide);
		KeyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		lastFacingSide = "LEFT";
		SetAcceleration(Player::PlayerStates::LEFT, m_isAttacking, lastFacingSide);
		KeyPressed = true;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		lastFacingSide = "RIGHT";
		SetAcceleration(Player::PlayerStates::RIGHT, m_isAttacking, lastFacingSide);
		KeyPressed = true;
	}
	

	if (!KeyPressed)
		SetAcceleration(Player::PlayerStates::IDLE, m_isAttacking, lastFacingSide);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		m_currentMagic->ShotProjectile(lastFacingSide, Renderer.GetPosition());
	}

	Renderer.PlayAnimation();
	AssignSkillpoints();
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
	++m_skillpoints;
	m_exp = 0;

}

int Player::GetExpPercentage()
{
	return (100 * m_exp) / (m_expNeededToLevelUp * m_level); // 100 at front stands for 100%
}

int Player::GetSpeed()
{
	return m_speed-1;
}

int Player::GetSkillpoints()
{
	return m_skillpoints;
}

void Player::AssignSkillpoints()
{
	if (m_skillpoints > 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { m_swordDamage += 1; m_skillpoints--; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { m_magicPower += 1; m_skillpoints--; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) { 
			m_speed += 1; m_skillpoints--;
			m_maxSpeed = sf::Vector2f(50.f * m_speed, 50.f * m_speed);
			m_maxSpeedInv = sf::Vector2f(-50.f * m_speed, -50.f * m_speed);
		}
	}
}

int Player::GetMagicPower()
{
	return m_magicPower;
}

void Player::DrawProjectilesTest(sf::RenderWindow & window, sf::Time & frameTime)
{
	m_currentMagic->DrawProjectiles(window, frameTime);
}


