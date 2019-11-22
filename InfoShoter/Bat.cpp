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
	healthBarOffset = sf::Vector2i(37, 72);
	boundingBox = {sf::Vector2f(15.f,15.f),sf::Vector2f(70.f,70.f),sf::Vector2f(15.f,70.f), sf::Vector2f(70.f,15.f) };
	minimapOffset = sf::Vector2f(35.f, 35.f);
	healthPoints = 100;
	maxHealthPoints = 100;
}