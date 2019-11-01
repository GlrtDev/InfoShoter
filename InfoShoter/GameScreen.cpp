#include "GameScreen.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include "SFMLOrthogonalLayer.hpp"

#include <tmxlite/Map.hpp>

#include "Player.h"

GameScreen::GameScreen(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}

int GameScreen::Run(sf::RenderWindow & window)
{
	sf::View view;
	view.setViewport(sf::FloatRect(0.f, 0.f, 1.5f, 2.f));
	window.setView(view);
	bool Running = true;
	sf::Event Event;
	tgui::Gui gui{ window };

	tmx::Map map;
	map.load("../assets/Level1TileMap.tmx");
	
	MapLayer layerZero(map, 0);
	MapLayer layerOne(map, 1);
	sf::Clock globalClock;
	sf::Clock frameClock;
	sf::Time frameTime;

	Player player;
	Player::PlayerDirections playerDirection = Player::PlayerDirections::IDLE;
	bool moveKeyPressed = false;
	while (Running)
	{
		view.setCenter(player.Renderer.GetPosition());

		view.move(sf::Vector2f(210,330));
		frameTime = frameClock.restart();
		//Verifying events
		while (window.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}

			if (Event.type == sf::Event::KeyReleased)
			{
				if (Event.key.code == sf::Keyboard::W || Event.key.code == sf::Keyboard::S) 
				{
					player.ResetVelocityY();
				}
				if (Event.key.code == sf::Keyboard::A || Event.key.code == sf::Keyboard::D) 
				{
					player.ResetVelocityX();
				}
			}
			gui.handleEvent(Event);
		}
		player.Control();

		player.Move(frameTime);

		sf::Time duration = globalClock.getElapsedTime();
		layerZero.update(duration);

		

		window.clear(sf::Color::Black);
		window.setView(view);
		window.draw(layerZero);
		
		
		player.Renderer.Draw(window, frameTime);
		window.draw(layerOne);
		gui.draw();
		window.display();
	}
	return (-1);
}
