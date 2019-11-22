#include "EnemyRenderer.h"



EnemyRenderer::EnemyRenderer()
{
	healthBar.setSize(sf::Vector2f(25.f, 4.f));
	healthBar.setFillColor(sf::Color(0, 255, 0, 170));
	healthBarBackground.setSize(sf::Vector2f(25.f, 4.f));
	healthBarBackground.setFillColor(sf::Color(0, 0, 0, 100));

	minimapDot.setRadius(10.f);
	minimapDot.setFillColor(sf::Color(255, 0, 0, 255));

	for (int i = 0; i < 4; i++) {
		boundingBoxDots[i].setRadius(2.f);
		boundingBoxDots[i].setFillColor(sf::Color(255, 0, 0, 255));
	}
}


EnemyRenderer::~EnemyRenderer()
{
}

void EnemyRenderer::Draw(sf::RenderWindow &window, sf::Time &frameTime)
{
	animatedSprite.update(frameTime); //sometimes throw exception; vector subscript out of range
	window.draw(animatedSprite);
	window.draw(healthBarBackground);
	window.draw(healthBar);
	for (int i = 0; i < 4; i++) 
		window.draw(boundingBoxDots[i]);
}

void EnemyRenderer::DrawOnMinimap(sf::RenderWindow &window)
{
	minimapDot.setPosition(animatedSprite.getPosition() + minimapOffset);
	window.draw(minimapDot);
}

sf::Vector2f EnemyRenderer::GetPosition()
{
	return animatedSprite.getPosition();
}

void EnemyRenderer::ChangeAnimation(int i)
{
	switch (i) {
	case -1:
			currentAnimation = &walkingAnimationLeft;
			animatedSprite.play(*currentAnimation);
			break;
		
	case 1:
			currentAnimation = &walkingAnimationRight;
			animatedSprite.play(*currentAnimation);
			break;
	default:
		break;
	}
}
