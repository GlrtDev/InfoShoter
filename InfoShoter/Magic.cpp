#include "Magic.h"
#include <random>

const std::string magicNames[20]{ "Dying Light", "Scarlet","Dreamwatcher","Engraved Pole","Oblivion","Clemency","Stalk of Truth","Tormented Pole","Crazed Grand Staff","Fireweaver","Nirvana","Pursuit","Peacekeeper's Scepter","Vengeance Branch","Quicksilver","Twister","Dreambinder","Heartless Spire","Mage's Greatstaff" };

Magic::Magic(int level, float seedAsFrameTimeSec, int playerMagicLevel) : m_projectileLoaded(true), m_playerMagicLevel(playerMagicLevel)
{
	std::minstd_rand0 randomNumberGenerator;
	randomNumberGenerator.seed(seedAsFrameTimeSec);
	std::uniform_int_distribution<int> randRange(50, 100);
	std::uniform_int_distribution<int> nameRange(0, 19);
	auto random1 = std::bind(randRange, randomNumberGenerator);
	std::uniform_int_distribution<int> randRangeForType(0, 2);
	auto random2 = std::bind(randRangeForType, randomNumberGenerator);
	m_type = random2();
	m_name = magicNames[nameRange(randomNumberGenerator)];
	m_damage = level * (random1()+5) * (1 + m_playerMagicLevel / 3.0) * (1 - (m_type / 6.f));
	m_speed = random1() * (1 + (m_type / 6.f)) * (1 + m_playerMagicLevel / 30.0);
	m_manaCost = (m_damage + m_speed/4.f)*0.05f;
	m_rechargeTime = 5*((float)m_damage/ ((float)m_speed * level * (m_playerMagicLevel + 1)));
	sf::Color ProjectileColor(122.5f * random2() + 1, 122.5f * random2() + 1, 122.5f * random2(), 255);
	projectile = new Projectile(m_damage, m_speed, m_type, ProjectileColor);
	switch (m_type) {
	case 0:
		m_iconTexture.loadFromFile("../Sprites/Icons/Fire.png", { 0, 0, 16, 16 });
		break;
	case 1:
		m_iconTexture.loadFromFile("../Sprites/Icons/Ice3.png", { 0, 0, 24, 24 });
		break;
	case 2:
		m_iconTexture.loadFromFile("../Sprites/Icons/Wind.png", { 0, 0, 16, 16 });
		break;
	}
	m_iconTexture.setSmooth(false);
}


Magic::~Magic()
{
}

bool Magic::ShotProjectile(const std::string &lastFacingSide, sf::Vector2f startPosition)
{
	if (m_projectileLoaded) {
		projectile->SetDirection(lastFacingSide, startPosition);
		m_projectiles.push_back(*projectile);
		m_projectileLoaded = false;
		return true;
	}
	return false;
}

void Magic::DrawProjectiles(sf::RenderWindow & window, sf::Time & frameTime)
{
	for (auto projectile = m_projectiles.begin(); projectile != m_projectiles.end(); ++projectile) {

		if (projectile->CheckStatus()) {
			m_projectiles.erase(projectile);
			break;
		}
	}

	for (auto projectile = m_projectiles.begin(); projectile != m_projectiles.end(); ++projectile) {
		
			projectile->Move(frameTime);
			projectile->Draw(window, frameTime);
	}
		
}

std::string Magic::GetName()
{
	return m_name + ((m_type == 0) ? " of Fire" 
					: (m_type == 1) ? " of Ice" 
					: " of Wind" ) ;
}

int Magic::GetDamage()
{
	return m_damage;
}

int Magic::GetSpeed()
{
	return m_speed;
}

int Magic::GetManaCost()
{
	return m_manaCost;
}

float Magic::GetRechargeTime()
{
	return m_rechargeTime;
}

int Magic::GetType()
{
	return m_type;
}

sf::Texture Magic::GetIconTexture()
{
	return m_iconTexture;
}

int Magic::CalculateRecharge(sf::Time & frameTime)
{
	static sf::Time timeRecharging;

	if (!m_projectileLoaded)
		timeRecharging += frameTime;

	if (timeRecharging.asSeconds() >= m_rechargeTime) {
		timeRecharging = sf::Time::Zero;
		m_projectileLoaded = true;
	}
	return (timeRecharging == sf::Time::Zero) ? 0 : 100 - ((timeRecharging.asSeconds() / m_rechargeTime ) * 100);
}

std::vector<Projectile>* Magic::GetProjectiles()
{
	return &m_projectiles;
}

void Magic::LevelUp()
{
	m_damage *= (1 + m_playerMagicLevel / 3.0);
	m_speed *=(1 + m_playerMagicLevel / 30.0);
	m_manaCost = (m_damage + m_speed / 4.f)*0.05f;
	m_rechargeTime -=  ( (1/(m_playerMagicLevel+1)) * m_rechargeTime );
}

