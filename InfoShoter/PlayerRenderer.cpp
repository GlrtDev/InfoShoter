#include "PlayerRenderer.h"



PlayerRenderer::PlayerRenderer(sf::Vector2f startPosition) : animatedSprite(sf::seconds(0.1f), false, true)
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

	attackAnimationDown.setSpriteSheet(texture);
	attackAnimationLeft.setSpriteSheet(texture);
	attackAnimationRight.setSpriteSheet(texture);
	attackAnimationUp.setSpriteSheet(texture);

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

	for (int i = 2; i < 5; i++)
		attackAnimationDown.addFrame(sf::IntRect(84 * i, 252, 84, 84));

	for (int i = 5; i < 8; i++)
		attackAnimationUp.addFrame(sf::IntRect(84 * i, 252, 84, 84));

	for (int i = 0; i < 3; i++)
		attackAnimationRight.addFrame(sf::IntRect(84 * i, 336, 84, 84));

	for (int i = 3; i < 6; i++)
		attackAnimationLeft.addFrame(sf::IntRect(84 * i, 336, 84, 84));

	
	// set up AnimatedSprite
	//AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setPosition(startPosition);
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
	case 5:
		currentAnimation = &attackAnimationUp;
		break;
	case 6:
		currentAnimation = &attackAnimationDown;
		break;
	case 7:
		currentAnimation = &attackAnimationRight;
		break;
	case 8:
		currentAnimation = &attackAnimationLeft;
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

void PlayerRenderer::SetPosition(sf::Vector2f position_)
{
	animatedSprite.setPosition(position_);
}

void PlayerRenderer::Move(sf::Vector2f movement, sf::Time &frameTime)
{
	animatedSprite.move(movement * frameTime.asSeconds());
}
