#include "ParticleRenderer.h"



ParticleRenderer::ParticleRenderer()
{
	if (!m_textureFireball.loadFromFile("../Sprites/GameFX/FireBall_64x64.png")){
		std::cout << "Failed to load Fireball spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;
	if (!m_textureIce.loadFromFile("../Sprites/GameFX/IcePick_64x64.png")){
		std::cout << "Failed to load ice spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;
	if (!m_textureTornado.loadFromFile("../Sprites/GameFX/TornadoLoop_96x96.png")){
		std::cout << "Failed to load wind spritesheet!" << std::endl;
	}
	else
		std::cout << "gooooodsdd" << std::endl;

	m_fireballFly.setSpriteSheet(m_textureFireball);

	for (int i = 0; i < 45; i++)
		m_fireballFly.addFrame(sf::IntRect(64 * i, 0, 64, 64));

	m_iceFly.setSpriteSheet(m_textureIce);

	for (int i = 0; i < 30; i++)
		m_iceFly.addFrame(sf::IntRect(64 * i, 0, 64, 64));

	m_tornadoFly.setSpriteSheet(m_textureTornado);

	for (int i = 0; i < 60; i++)
		m_tornadoFly.addFrame(sf::IntRect(96 * i, 0, 96, 96));
	collisionPoint.setRadius(2.f);
	collisionPoint.setFillColor(sf::Color::Black);
}


ParticleRenderer::~ParticleRenderer()
{
}

void ParticleRenderer::Draw(sf::RenderWindow & window, sf::Time & frameTime)
{
	collisionPoint.setPosition(m_animatedSprite.getPosition() + sf::Vector2f(48, 60));
	m_animatedSprite.update(5.f * frameTime);
	window.draw(m_animatedSprite);
	window.draw(collisionPoint);
}

