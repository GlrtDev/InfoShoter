#include "Roque.h"



Roque::Roque(std::queue<sf::Vector2f> path_, int level_) : Enemy(path_, level_) {
	if (!m_texture.loadFromFile("../Sprites/EnemySprites/rogue like run.png"))
	{
		std::cout << "Failed to load roque  spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;

	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationRight.setSpriteSheet(m_texture);
	for (int i = 0; i < 6; i++)
		m_walkingAnimationLeft.addFrame(sf::IntRect(24* i, 24, 24, 25));
	for (int i = 0; i < 6; i++)
		m_walkingAnimationRight.addFrame(sf::IntRect(24 * i, 0, 24, 25));
	m_velocity = 62.f;
	sf::Vector2f startPosition(m_path.front());  m_path.pop();
	m_positionOffset = sf::Vector2f(15.f, 30.f);
	m_animatedSprite.setPosition(startPosition + m_positionOffset);
	m_currentAnimation = &m_walkingAnimationLeft;
	m_animatedSprite.play(*m_currentAnimation);
	m_animatedSprite.setScale(sf::Vector2f(1.8f, 1.8f));
	m_healthBarOffset = sf::Vector2i(10, 50);
	m_boundingBox = { sf::Vector2f(-10.f,-10.f),sf::Vector2f(45.f,45.f),sf::Vector2f(-10.f,45.f), sf::Vector2f(45.f,-10.f) };
	m_minimapOffset = sf::Vector2f(35.f, 35.f);
	

	m_baseHealth = 200;
	m_healthLevelMultipler = 50;
	m_baseExp = 100;
	m_expMultipler = 25;
	InitializeEnemy();
	m_healthPoints = m_maxHealthPoints;
}


Roque::~Roque()
{
}
