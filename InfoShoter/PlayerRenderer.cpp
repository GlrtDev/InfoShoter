#include "PlayerRenderer.h"



PlayerRenderer::PlayerRenderer(sf::Vector2f startPosition) : m_animatedSprite(sf::seconds(0.1f), false, true)
{
	if (!m_texture.loadFromFile("../Sprites/4 directional character/knight iso char.png"))
	{
		std::cout << "Failed to load player spritesheet!" << std::endl;
	}
	else
		std::cout << "goooood" << std::endl;

	m_idleAnimation.setSpriteSheet(m_texture);
	m_walkingAnimationDown.setSpriteSheet(m_texture);
	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationRight.setSpriteSheet(m_texture);
	m_walkingAnimationUp.setSpriteSheet(m_texture);

	m_attackAnimationDown.setSpriteSheet(m_texture);
	m_attackAnimationLeft.setSpriteSheet(m_texture);
	m_attackAnimationRight.setSpriteSheet(m_texture);
	m_attackAnimationUp.setSpriteSheet(m_texture);

	for(int i = 0; i<4; i++)
		m_idleAnimation.addFrame(sf::IntRect(84*i, 0, 84, 84));

	for (int i = 0; i < 4; i++)
		m_walkingAnimationDown.addFrame(sf::IntRect(84 * (i+4), 0, 84, 84));
		m_walkingAnimationDown.addFrame(sf::IntRect(0, 84, 84, 84));

	for (int i = 0; i < 5; i++)
		m_walkingAnimationUp.addFrame(sf::IntRect(84*(i+1), 84, 84, 84));
	
	for (int i = 0; i < 2; i++)
		m_walkingAnimationRight.addFrame(sf::IntRect(84 * (i + 6), 84, 84, 84));
	for (int i = 0; i < 4; i++)
		m_walkingAnimationRight.addFrame(sf::IntRect(84 * i , 168, 84, 84));

	for (int i = 0; i < 4; i++)
		m_walkingAnimationLeft.addFrame(sf::IntRect(84 * (i+4), 168, 84, 84));
	for (int i = 0; i < 2; i++)
		m_walkingAnimationLeft.addFrame(sf::IntRect(84 * i, 252, 84, 84));

	for (int i = 2; i < 5; i++)
		m_attackAnimationDown.addFrame(sf::IntRect(84 * i, 252, 84, 84));

	for (int i = 5; i < 8; i++)
		m_attackAnimationUp.addFrame(sf::IntRect(84 * i, 252, 84, 84));

	for (int i = 0; i < 3; i++)
		m_attackAnimationRight.addFrame(sf::IntRect(84 * i, 336, 84, 84));

	for (int i = 3; i < 6; i++)
		m_attackAnimationLeft.addFrame(sf::IntRect(84 * i, 336, 84, 84));

	
	// set up AnimatedSprite
	//AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	m_animatedSprite.setPosition(startPosition);
	m_currentAnimation = &m_idleAnimation;
	m_animatedSprite.play(*m_currentAnimation);
	m_animatedSprite.setScale(sf::Vector2f(0.7f, 0.7f));

	m_PlayerDotMiniMap.setFillColor(sf::Color(250, 250, 50));
	m_PlayerDotMiniMap.setRadius(10.f);
}


PlayerRenderer::~PlayerRenderer()
{
}

void PlayerRenderer::ChangeAnimation(int animationIndex)
{
	switch (animationIndex)
	{
	case 0:
		m_currentAnimation = &m_walkingAnimationUp;
		break;
	case 1:
		m_currentAnimation = &m_walkingAnimationDown;
		break;
	case 2:
		m_currentAnimation = &m_walkingAnimationRight;
		break;
	case 3:
		m_currentAnimation = &m_walkingAnimationLeft;
		break;
	case 4:
		m_currentAnimation = &m_idleAnimation;
		break;
	case 5:
		m_currentAnimation = &m_attackAnimationUp;
		break;
	case 6:
		m_currentAnimation = &m_attackAnimationDown;
		break;
	case 7:
		m_currentAnimation = &m_attackAnimationRight;
		break;
	case 8:
		m_currentAnimation = &m_attackAnimationLeft;
		break;
		
	}
}

void PlayerRenderer::PlayAnimation()
{
	m_animatedSprite.play(*m_currentAnimation);
}

void PlayerRenderer::Draw(sf::RenderWindow &window, sf::Time &frameTime)
{
	m_animatedSprite.update(frameTime);
	window.draw(m_animatedSprite);
}
void PlayerRenderer::DrawOnMinimap(sf::RenderWindow &window, sf::Time &frameTime)
{
	m_PlayerDotMiniMap.setPosition(GetPosition());
	window.draw(m_PlayerDotMiniMap);
}
sf::Vector2f PlayerRenderer::GetPosition()
{
	return m_animatedSprite.getPosition();
}

void PlayerRenderer::SetPosition(sf::Vector2f position_)
{
	m_animatedSprite.setPosition(position_);
}

void PlayerRenderer::Move(sf::Vector2f movement, sf::Time &frameTime)
{
	m_animatedSprite.move(movement * frameTime.asSeconds());
	//std::cout << "x: " << m_animatedSprite.getPosition().x << "y: " << m_animatedSprite.getPosition().y << std::endl;
}
