#include "BlobSlime.h"



BlobSlime::BlobSlime(std::queue<sf::Vector2f> path_, int level_) : Enemy(path_, level_) {
	m_animationSpeed = 1.7f;
	if (!m_texture.loadFromFile("../Sprites/EnemySprites/blob move.png"))
	{
		std::cout << "Failed to load blob s spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;

	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationRight.setSpriteSheet(m_texture);
	for (int i = 0; i < 8; i++)
		m_walkingAnimationLeft.addFrame(sf::IntRect(80 * i, 80, 80, 80));
	for (int i = 0; i < 8; i++)
		m_walkingAnimationRight.addFrame(sf::IntRect(80 * i, 0, 80, 80));
	m_velocity = 80.f;
	sf::Vector2f startPosition(m_path.front());  m_path.pop();
	m_positionOffset = sf::Vector2f(15.f, 30.f);
	m_animatedSprite.setPosition(startPosition + m_positionOffset);
	//m_currentAnimation = &m_walkingAnimationLeft;
	//m_animatedSprite.play(*m_currentAnimation);
	m_animatedSprite.setScale(sf::Vector2f(0.8f, 0.8f));
	m_healthBarOffset = sf::Vector2i(23, 50);
	m_boundingBox = { sf::Vector2f(5.f,5.f),sf::Vector2f(60.f,60.f),sf::Vector2f(5.f,60.f), sf::Vector2f(60.f,5.f) };
	m_minimapOffset = sf::Vector2f(35.f, 35.f);

	m_baseHealth = 35;
	m_healthLevelMultipler = 10;
	m_baseExp = 10;
	m_expMultipler = 3;
	InitializeEnemy();
	m_healthPoints = m_maxHealthPoints;
}


BlobSlime::~BlobSlime()
{
}

void BlobSlime::Draw(sf::RenderWindow & window, sf::Time & frameTime) //TODO it didnt work, ask someone why
{
	sf::Time frameTime2 = frameTime * 5.f;
	Enemy::Draw(window, frameTime2);
}
