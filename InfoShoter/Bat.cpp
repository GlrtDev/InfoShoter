#include "Bat.h"

Bat::Bat(std::queue<sf::Vector2f> path_) : Enemy(path_) {
	if (!texture.loadFromFile("../Sprites/EnemySprites/eye monster idle.png"))
	{
		std::cout << "Failed to load bat moster spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;

	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationRight.setSpriteSheet(texture);
	for (int i = 0; i < 4; i++)
		walkingAnimationLeft.addFrame(sf::IntRect(320 * i, 0, 320, 320));
	for (int i = 4; i < 8; i++)
		walkingAnimationRight.addFrame(sf::IntRect(320 * i, 0, 320, 320));
	velocity = 70.f;
	sf::Vector2f startPosition(path.front());
	path.pop();
	animatedSprite.setPosition(startPosition);
	currentAnimation = &walkingAnimationLeft;
	animatedSprite.play(*currentAnimation);
	animatedSprite.setScale(sf::Vector2f(0.3f, 0.3f));

}