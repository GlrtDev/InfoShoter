#include "EnemyRenderer.h"
#include <stdexcept>  


EnemyRenderer::EnemyRenderer()
{
	m_healthBar.setSize(sf::Vector2f(25.f, 4.f));
	m_healthBar.setFillColor(sf::Color(0, 255, 0, 170));
	m_healthBarBackground.setSize(sf::Vector2f(25.f, 4.f));
	m_healthBarBackground.setFillColor(sf::Color(0, 0, 0, 100));

	m_minimapDot.setRadius(10.f);
	m_minimapDot.setFillColor(sf::Color(255, 0, 0, 255));

	for (int i = 0; i < 4; i++) {
		m_boundingBoxDots[i].setRadius(2.f);
		m_boundingBoxDots[i].setFillColor(sf::Color(255, 0, 0, 255));
	}
	//dead = false;
}


EnemyRenderer::~EnemyRenderer()
{
}

void EnemyRenderer::Draw(sf::RenderWindow &window, sf::Time &frameTime)
{
	//if (!dead) {
	try {
		m_animatedSprite.play(*m_currentAnimation);
		if(m_currentAnimation == &m_walkingAnimationLeft || m_currentAnimation == &m_walkingAnimationRight)
		m_animatedSprite.update(frameTime); //sometimes throw exception: vector subscript out of range
		window.draw(m_animatedSprite);
		window.draw(m_healthBarBackground);
		window.draw(m_healthBar);
		for (int i = 0; i < 4; i++)
			window.draw(m_boundingBoxDots[i]);
	}
	catch(const std::out_of_range &err)
	{
		std::cout << "out of range";
	}
	//}
}

void EnemyRenderer::DrawOnMinimap(sf::RenderWindow &window)
{
	m_minimapDot.setPosition(m_animatedSprite.getPosition() + m_minimapOffset);
	window.draw(m_minimapDot);
}

sf::Vector2f EnemyRenderer::GetPosition()
{
	return m_animatedSprite.getPosition();
}

void EnemyRenderer::ChangeAnimation(int i)
{
	switch (i) {
	case -1:
			m_currentAnimation = &m_walkingAnimationLeft;
			m_animatedSprite.play(*m_currentAnimation);
			break;
		
	case 1:
			m_currentAnimation = &m_walkingAnimationRight;
			m_animatedSprite.play(*m_currentAnimation);
			break;
	default:
		break;
	}
}
