#include "Player.h"
//#include <cmath>
//int Player::m_difficultLevel = 0;
//#define M_PI 3.14159265358979323846

Player::Player(sf::Vector2f startPosition, int difficult, std::string name) : m_boundingBox({ { sf::Vector2f(-35.f, -25.f), sf::Vector2f(-21.f, -25.f), sf::Vector2f(-35.f, -50.f), sf::Vector2f(-21.f, -50.f), sf::Vector2f(-21.f, 0.f), sf::Vector2f(-35.f, 0.f) } }),
Renderer(startPosition), m_expNeededToLevelUp(80), m_maxMana(10), m_swordDamageMultipler(1),
m_difficultLevel(difficult),m_name(name)
{
	m_speed = 4 - m_difficultLevel;
	m_maxSpeed = sf::Vector2f(50.f * m_speed, 50.f * m_speed);
	m_maxSpeedInv = sf::Vector2f(-50.f * m_speed, -50.f * m_speed);
	m_swordDamage = 7 - m_difficultLevel;
	m_level = 1;
	m_exp = 0;
	m_skillpoints = 0;
	m_magicPower = 0;
	//m_currentMagic = new Magic(1,11.f,1);
	m_currentMagic = nullptr;
	m_equipableMagic = nullptr;
	m_mana = m_maxMana;
	
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

void Player::SetAcceleration(PlayerStates direction, bool isAttacking, const std::string &lastFacingSide)
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
		if (m_currentMagic != nullptr)
			if (m_currentMagic->GetManaCost() <= m_mana)	
				if(m_currentMagic->ShotProjectile(lastFacingSide, Renderer.GetPosition()))
					m_mana -= m_currentMagic->GetManaCost();

	}

	if (m_equipableMagic != nullptr) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			m_currentMagic = m_equipableMagic;
			m_equipableMagic = nullptr;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			m_equipableMagic = nullptr;
		}
	}
	//TO DO make this look good
	Renderer.PlayAnimation();
	AssignSkillpoints();
}

int Player::GetDamage()
{
	return m_swordDamage * m_swordDamageMultipler;
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
	m_swordDamage += m_level/2;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) { m_swordDamageMultipler += 0.5f; m_skillpoints--; }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) { 
			m_magicPower += 1; m_skillpoints--;
			if(m_currentMagic != nullptr)
				m_currentMagic->LevelUp();
			m_maxMana = 10 * m_magicPower * m_level;
			m_mana = m_maxMana;
		}
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

Magic * Player::GetCurrentMagic()
{
	return m_currentMagic;
}

void Player::DrawProjectilesTest(sf::RenderWindow & window, sf::Time & frameTime)
{
	if(m_currentMagic != nullptr)
	m_currentMagic->DrawProjectiles(window, frameTime);
}

void Player::SetEquipableMagic(Magic * newMagic)
{
	m_equipableMagic = newMagic;
}

Magic* Player::GetEquipableMagic()
{
	return m_equipableMagic;
}

int Player::GetManaPercentage()
{
	return 100 * (m_mana / m_maxMana);
}

void Player::Update(sf::Time & frameTime)
{
	if (m_mana < m_maxMana)
		m_mana += frameTime.asSeconds()*(m_maxMana/(8.f - m_swordDamage* 0.1f));
}

float Player::GetMana()
{
	return m_mana;
}

std::string Player::GetDifficultLevel()
{
	//(m_difficultLevel == 0 ? "EASY" : (m_difficultLevel == 1) ? "NORMAL" : "HARD");
	switch (m_difficultLevel) {
	case 0:
		return "EASY";
		break;
	case 1:
		return "NORMAL";
		break;
	case 2:
		return "HARD";
		break;
	default:
		return "???";
		break;
	}
}

std::string Player::GetName()
{
	return m_name;
}

Score Player::GetScore()
{
	Score score = { m_name, GetDifficultLevel(), 0 , m_level , m_swordDamage , m_magicPower , m_speed};
	return score;
}

