#include "PlayerRenderer.h"



PlayerRenderer::PlayerRenderer() : animatedSprite(sf::seconds(0.1f), false, true)
{
	if (!texture.loadFromFile("../Sprites/4 directional character/knight iso char.png"))
	{
		std::cout << "Failed to load player spritesheet!" << std::endl;
	}
	else
		std::cout << "goooood" << std::endl;

	idleAnimation.setSpriteSheet(texture);
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationUp.setSpriteSheet(texture);

	for(int i = 0; i<4; i++)
		idleAnimation.addFrame(sf::IntRect(84*i, 0, 84, 84));

	for (int i = 0; i < 4; i++)
		walkingAnimationDown.addFrame(sf::IntRect(84 * (i+4), 0, 84, 84));
		walkingAnimationDown.addFrame(sf::IntRect(0, 84, 84, 84));

	for (int i = 0; i < 5; i++)
		walkingAnimationUp.addFrame(sf::IntRect(84*(i+1), 84, 84, 84));
	
	for (int i = 0; i < 2; i++)
		walkingAnimationRight.addFrame(sf::IntRect(84 * (i + 6), 84, 84, 84));
	for (int i = 0; i < 4; i++)
		walkingAnimationRight.addFrame(sf::IntRect(84 * i , 168, 84, 84));

	for (int i = 0; i < 4; i++)
		walkingAnimationLeft.addFrame(sf::IntRect(84 * (i+4), 168, 84, 84));
	for (int i = 0; i < 2; i++)
		walkingAnimationLeft.addFrame(sf::IntRect(84 * i, 252, 84, 84));

	

	
	// set up AnimatedSprite
	//AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	//animatedSprite.setPosition(sf::Vector2f(10,10));
	currentAnimation = &idleAnimation;
	animatedSprite.play(*currentAnimation);
	
}


PlayerRenderer::~PlayerRenderer()
{
}

void PlayerRenderer::ChangeAnimation(int animationIndex)
{
	switch (animationIndex)
	{
	case 0:
		currentAnimation = &walkingAnimationUp;
		break;
	case 1:
		currentAnimation = &walkingAnimationDown;
		break;
	case 2:
		currentAnimation = &walkingAnimationRight;
		break;
	case 3:
		currentAnimation = &walkingAnimationLeft;
		break;
	case 4:
		currentAnimation = &idleAnimation;
		break;
	}
	

}

void PlayerRenderer::PlayAnimation()
{
	animatedSprite.play(*currentAnimation);
}

void PlayerRenderer::Draw(sf::RenderWindow &window, sf::Time &frameTime)
{
	animatedSprite.update(frameTime);
	window.draw(animatedSprite);
}

sf::Vector2f PlayerRenderer::GetPosition()
{
	return animatedSprite.getPosition();
}

void PlayerRenderer::Move(sf::Vector2f movement, sf::Time &frameTime)
{
	animatedSprite.move(movement * frameTime.asSeconds());
}
