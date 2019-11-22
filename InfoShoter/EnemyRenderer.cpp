#include "EnemyRenderer.h"



EnemyRenderer::EnemyRenderer()
{
}


EnemyRenderer::~EnemyRenderer()
{
}

void EnemyRenderer::Draw(sf::RenderWindow &window, sf::Time &frameTime)
{
	animatedSprite.update(frameTime);
	window.draw(animatedSprite);
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
