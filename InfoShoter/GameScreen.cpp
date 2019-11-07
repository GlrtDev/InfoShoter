#include "GameScreen.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include "SFMLOrthogonalLayer.hpp"

#include <tmxlite/Map.hpp>

#include "Player.h"
#include "EventHandler.h"
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

	/*sf::CircleShape shape[5];
	for (int i = 1; i < 5; i++) {
		shape[i].setFillColor(sf::Color(100, 250, 50));
		shape[i].setRadius(2);
	}*/
	tmx::Map map;
	map.load("../assets/Level1TileMap.tmx");
	
	MapLayer layerZero(map, 0);
	MapLayer layerOne(map, 1);
	tmx::ObjectGroup collisionLayer;
	/*tmx::ObjectGroup collisionLayer;*/
	int i = 1;
	for (auto& layer : map.getLayers()) // set layer for collision handle
	{ 
		if (layer->getType() == tmx::Layer::Type::Object)
		{
			collisionLayer = layer->getLayerAs<tmx::ObjectGroup>();
			std::cout << "\nleyer " << i << " is a collision layer\n";
			break;
		}
		else 
		{
			std::cout << "\nleyer " << i << " is not collision layer\n";
			i++;
		}
	}

	sf::Clock globalClock;
	sf::Clock frameClock;
	sf::Time frameTime;

	sf::Vector2f startPosition(350.f, 300.f);
	Player player(startPosition);
	Player::PlayerStates playerDirection = Player::PlayerStates::IDLE;

	while (Running)
	{
		view.setCenter(player.Renderer.GetPosition()+ sf::Vector2f(210, 330));

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
		//COLISION DETECTION START
		EventHandler::CollisionDetection(player, collisionLayer, frameTime);
		//COLLISION DETECT END
		window.clear(sf::Color::Black);
		window.setView(view);
		window.draw(layerZero);
		
		
		player.Renderer.Draw(window, frameTime);
		window.draw(layerOne);
		gui.draw();
		/*window.draw(shape[1]);
		window.draw(shape[2]);
		window.draw(shape[3]);
		window.draw(shape[4]);*/
		window.display();
	}
	return (-1);
}
