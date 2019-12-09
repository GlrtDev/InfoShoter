#include "Goblin.h"



Goblin::Goblin(std::queue<sf::Vector2f> path_, int level_) : Enemy(path_, level_) {
	if (!m_texture.loadFromFile("../Sprites/EnemySprites/goblin run.png"))
	{
		std::cout << "Failed to load goblin spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;

	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationRight.setSpriteSheet(m_texture);
	for (int i = 0; i < 6; i++)
		m_walkingAnimationLeft.addFrame(sf::IntRect(64 * i, 64, 64, 64));
	for (int i = 0; i < 6; i++)
		m_walkingAnimationRight.addFrame(sf::IntRect(64 * i, 0, 64, 64));
	m_velocity = 60.f;
	sf::Vector2f startPosition(m_path.front());  m_path.pop();
	m_positionOffset = sf::Vector2f(5.f, 15.f);
	m_animatedSprite.setPosition(startPosition + m_positionOffset);
	m_currentAnimation = &m_walkingAnimationLeft;
	m_animatedSprite.play(*m_currentAnimation);
	//m_animatedSprite.setScale(sf::Vector2f(0.7f, 0.7f));
	m_healthBarOffset = sf::Vector2i(22, 58);
	m_boundingBox = { sf::Vector2f(0.f,5.f),sf::Vector2f(60.f,60.f),sf::Vector2f(0.f,60.f), sf::Vector2f(60.f,5.f) };
	m_minimapOffset = sf::Vector2f(35.f, 35.f);

	m_baseHealth = 70;
	m_healthLevelMultipler = 14;
	m_baseExp = 17;
	m_expMultipler = 6;
	InitializeEnemy();
	m_healthPoints = m_maxHealthPoints;
}


Goblin::~Goblin()
{
}
