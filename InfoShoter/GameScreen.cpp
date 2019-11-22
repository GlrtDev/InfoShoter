#include <deque>

#include "GameScreen.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include "SFMLOrthogonalLayer.hpp"

#include <tmxlite/Map.hpp>

#include "Player.h"
#include "Bat.h"
#include "EventHandler.h"
#include <vector>
GameScreen::GameScreen(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}

int GameScreen::Run(sf::RenderWindow & window)
{
	std::queue<sf::Vector2f> path[3];
	*path = EventHandler::initializePaths(path);
	
	sf::View view;
	view.setViewport(sf::FloatRect(0.f, 0.f, 2.25f, 4.f)); // 9:16
	

	sf::View miniMap;
	miniMap.setViewport(sf::FloatRect(0.f, 0.75f, 0.25f, 0.25f)); // 9:16
	
	sf::Vector2f cameraCorrection(310.f, 400.f);
	bool Running = true;
	sf::Event Event;
	tgui::Gui gui{ window };

	//TO DO (make this prettier)
	sf::CircleShape PlayerDotMiniMap;
	PlayerDotMiniMap.setFillColor(sf::Color(250, 250, 50));
	PlayerDotMiniMap.setRadius(10.f);

	

	
	tmx::Map map;
	map.load("../assets/Level1TileMap.tmx");
	
	MapLayer groundLayer(map, 0);
	MapLayer upperGroundLayer(map, 1);
	MapLayer decorativeLayer(map, 2);
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

	sf::Clock spawnPeriod;
	sf::Clock timeBetwenWaves;
	sf::Clock globalClock;
	sf::Clock frameClock;
	sf::Time frameTime;

	sf::Vector2f startPosition(350.f, 300.f);
	Player player(startPosition);

	std::vector<Enemy> enemiesLiving;
	std::vector<Enemy> enemySpawnQueue;
	bool waveStarted=false;
	int waveNumber = 0;

	Bat Bat(path[0]);
	

	enemySpawnQueue.push_back(Bat); 
	enemySpawnQueue.push_back(Bat);
	enemySpawnQueue.push_back(Bat);
	enemySpawnQueue.push_back(Bat);
	enemySpawnQueue.push_back(Bat);

	while (Running)
	{
		view.setCenter(player.Renderer.GetPosition()+ cameraCorrection);
		miniMap.setCenter(player.Renderer.GetPosition());
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

		
		PlayerDotMiniMap.setPosition(player.Renderer.GetPosition());

		//std::cout << std::endl << player.Renderer.GetPosition().x<<" " << player.Renderer.GetPosition().y;
		player.Control();
		player.Move(frameTime);

		if (timeBetwenWaves.getElapsedTime().asSeconds() > 1 && !waveStarted) {
			waveStarted = true;
			timeBetwenWaves.restart();
		}

			if (spawnPeriod.getElapsedTime().asSeconds() > 2 && !enemySpawnQueue.empty() && waveStarted) {
				enemiesLiving.push_back(enemySpawnQueue.back());
				enemySpawnQueue.pop_back();
				spawnPeriod.restart();
			}
		
			if (enemiesLiving.size() == 0 && waveStarted)
				waveStarted = false;

			for (auto& liveEnemy : enemiesLiving) {
				liveEnemy.FollowPath(frameTime);
			}
			//std::cout << waveStarted;



		sf::Time duration = globalClock.getElapsedTime();
		decorativeLayer.update(duration);
		//COLISION DETECTION START
		EventHandler::CollisionDetection(player, collisionLayer, frameTime, enemiesLiving); //walls collisions
		//COLLISION DETECT END
		window.clear(sf::Color::Black);

		window.setView(view);
		window.draw(groundLayer);
		player.Renderer.Draw(window, frameTime);
		window.draw(upperGroundLayer);

		for (auto& en : enemiesLiving)
			en.Draw(window, frameTime);

		window.draw(decorativeLayer);
		

		window.setView(miniMap);

		

		window.draw(groundLayer);
		for (auto& en : enemiesLiving)
			en.DrawOnMinimap(window);
		window.draw(PlayerDotMiniMap);
		gui.draw();
		//player.Renderer.Draw(window, frameTime);
		//window.draw(upperGroundLayer);
		window.display();
	}
	return (-1);
}
