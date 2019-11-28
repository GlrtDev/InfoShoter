#include "Knight.h"



Knight::Knight(std::queue<sf::Vector2f> path_, int level_) : Enemy(path_, level_) {
	if (!m_texture.loadFromFile("../Sprites/EnemySprites/knight walk.png"))
	{
		std::cout << "Failed to load knight spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;

	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationRight.setSpriteSheet(m_texture);
	for (int i = 7; i >= 0; i--)
		m_walkingAnimationLeft.addFrame(sf::IntRect(42 * i, 0, 42, 42));
	for (int i = 0; i < 8; i++)
		m_walkingAnimationRight.addFrame(sf::IntRect(42 * i, 42, 42, 42));
	
	m_velocity = 30.f;
	sf::Vector2f startPosition(m_path.front()); m_path.pop();
	m_animatedSprite.setPosition(startPosition);
	m_currentAnimation = &m_walkingAnimationLeft;
	m_animatedSprite.play(*m_currentAnimation);
	m_animatedSprite.setScale(sf::Vector2f(1.8f, 1.8f));
	m_healthBarOffset = sf::Vector2i(28, 72);
	m_boundingBox = { sf::Vector2f(10.f,15.f),sf::Vector2f(70.f,70.f),sf::Vector2f(10.f,70.f), sf::Vector2f(70.f,15.f) };
	m_minimapOffset = sf::Vector2f(35.f, 35.f);

	m_baseHealth = 150;
	m_healthLevelMultipler = 40;
	m_baseExp = 15;
	m_expMultipler = 4;
	InitializeEnemy();
	m_healthPoints = m_maxHealthPoints;
}


Knight::~Knight()
{
}
