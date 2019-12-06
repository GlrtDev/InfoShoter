#include "BlobMinion.h"



BlobMinion::BlobMinion(std::queue<sf::Vector2f> path_, int level_) : Enemy(path_, level_) {
	if (!m_texture.loadFromFile("../Sprites/EnemySprites/blob minion walk.png"))
	{
		std::cout << "Failed to load bat moster spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;

	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationRight.setSpriteSheet(m_texture);
	for (int i = 0; i < 8; i++)
		m_walkingAnimationLeft.addFrame(sf::IntRect(80 * i, 80, 80, 80));
	for (int i = 0; i < 8; i++)
		m_walkingAnimationRight.addFrame(sf::IntRect(80 * i, 0, 80, 80));
	m_velocity = 20.f;
	sf::Vector2f startPosition(m_path.front());  m_path.pop();
	m_positionOffset = sf::Vector2f(-10.f, -35.f);
	m_animatedSprite.setPosition(startPosition + m_positionOffset);
	m_currentAnimation = &m_walkingAnimationLeft;
	m_animatedSprite.play(*m_currentAnimation);
	m_animatedSprite.setScale(sf::Vector2f(1.3f, 1.3f));
	m_healthBarOffset = sf::Vector2i(37, 110);
	m_boundingBox = { sf::Vector2f(15.f,40.f),sf::Vector2f(80.f,110.f),sf::Vector2f(15.f,110.f), sf::Vector2f(80.f,40.f) };
	m_minimapOffset = sf::Vector2f(35.f, 35.f);

	m_baseHealth = 500;
	m_healthLevelMultipler = 100;
	m_baseExp = 100;
	m_expMultipler = 20;
	InitializeEnemy();
	m_healthPoints = m_maxHealthPoints;
}


BlobMinion::~BlobMinion()
{
}
