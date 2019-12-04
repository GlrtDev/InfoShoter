#include "Magic.h"
#include <random>

const std::string magicNames[20]{ "Dying Light", "Scarlet","Dreamwatcher","Engraved Pole","Oblivion","Clemency","Stalk of Truth","Tormented Pole","Crazed Grand Staff","Fireweaver","Nirvana","Pursuit","Peacekeeper's Scepter","Vengeance Branch","Quicksilver","Twister","Dreambinder","Heartless Spire","Mage's Greatstaff" };

Magic::Magic(int level, float seedAsFrameTimeSec) : m_projectileLoaded(true)
{
	std::minstd_rand0 randomNumberGenerator;
	std::uniform_int_distribution<int> randRange(50, 100);
	std::uniform_int_distribution<int> nameRange(0, 19);
	//randRange(randomNumberGenerator);
	randomNumberGenerator.seed(seedAsFrameTimeSec);
	m_name = magicNames[nameRange(randomNumberGenerator)];
	m_damage = level * randRange(randomNumberGenerator);
	m_speed = randRange(randomNumberGenerator);
	m_manaCost = m_damage + m_speed;
	m_rechargeTime = 7 - (m_speed/25 + m_manaCost/(50*level));
	std::uniform_int_distribution<int> randRangeForType(0, 2);
	m_type = randRangeForType(randomNumberGenerator);// change to %3 later
	projectile = new Projectile(m_damage, m_speed, m_type);
	
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
	//m_icon = tgui::Picture::create(icon_texture,false);
	//m_currentAnimation = &m_walkingAnimationLeft;
	//m_animatedSprite.play(*m_currentAnimation);
}


Magic::~Magic()
{
}

void Magic::ShotProjectile(const std::string lastFacingSide, sf::Vector2f startPosition)
{
	if (m_projectileLoaded) {
		projectile->SetDirection(lastFacingSide, startPosition);
		m_projectiles.push_back(*projectile);
		m_projectileLoaded = false;
	}
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

