#include "Bat.h"

Bat::Bat(std::queue<sf::Vector2f> path_,int level_) : Enemy(path_, level_) {
	if (!m_texture.loadFromFile("../Sprites/EnemySprites/eye monster idle.png"))
	{
		std::cout << "Failed to load bat moster spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;

	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationRight.setSpriteSheet(m_texture);
	for (int i = 0; i < 4; i++)
		m_walkingAnimationLeft.addFrame(sf::IntRect(320 * i, 0, 320, 320));
	for (int i = 4; i < 8; i++)
		m_walkingAnimationRight.addFrame(sf::IntRect(320 * i, 0, 320, 320));
	m_velocity = 70.f;
	sf::Vector2f startPosition(m_path.front());  m_path.pop();
	m_animatedSprite.setPosition(startPosition);
	m_currentAnimation = &m_walkingAnimationLeft;
	m_animatedSprite.play(*m_currentAnimation);
	m_animatedSprite.setScale(sf::Vector2f(0.3f, 0.3f));
	m_healthBarOffset = sf::Vector2i(37, 72);
	m_boundingBox = {sf::Vector2f(15.f,15.f),sf::Vector2f(70.f,70.f),sf::Vector2f(15.f,70.f), sf::Vector2f(70.f,15.f) };
	m_minimapOffset = sf::Vector2f(35.f, 35.f);
	
	m_baseHealth = 50;
	m_healthLevelMultipler = 10;
	m_baseExp = 14;
	m_expMultipler = 5;
	InitializeEnemy();
	m_healthPoints = m_maxHealthPoints;
}