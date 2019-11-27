#include <string>
#include <math.h>
#include <random>

#include "GameScreen.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include "SFMLOrthogonalLayer.hpp"

#include <tmxlite/Map.hpp>

#include "Player.h"
#include "Bat.h"
#include "Knight.h"
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
	//sf::RectangleShape minimapBackground;
	//minimapBackground.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	//minimapBackground.setFillColor(sf::Color::Black);
	
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
	bool wavePrepared = false;
	int waveNumber = 0;
	int enemyUnitsPowerBase = 500;
	int enemyUnitsPowerMultipler = 100;
	std::default_random_engine randomNumberGenerator;
	std::uniform_int_distribution<int> randRange(1, 100);
	

	auto waveText = tgui::Label::create();
	waveText->getRenderer()->setFont(tgui::Font::Font("../assets/IMMORTAL.ttf"));
	waveText->getRenderer()->setBorders(5);
	waveText->getRenderer()->setBackgroundColor(tgui::Color::White);
	waveText->setPosition(1570, 780);
	waveText->setTextSize(28);

	auto waveCounter = tgui::Label::create();
	waveCounter->getRenderer()->setFont(tgui::Font::Font("../assets/IMMORTAL.ttf"));
	waveCounter->getRenderer()->setTextColor(tgui::Color::Red);
	waveCounter->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	waveCounter->setPosition(720, 450);
	waveCounter->setTextSize(68);

	auto experienceBar = tgui::ProgressBar::create();
	experienceBar->setPosition(1520, 1015);
	experienceBar->setSize(200, 20);
	experienceBar->getRenderer()->setBorders(3);
	experienceBar->getRenderer()->setFillColor(sf::Color(201, 129, 60, 200));

	auto PlayerGui = tgui::Label::create();
	PlayerGui->getRenderer()->setFont(tgui::Font::Font("../assets/IMMORTAL.ttf"));
	PlayerGui->getRenderer()->setTextColor(tgui::Color::Black);
	PlayerGui->getRenderer()->setBorders(5);
	PlayerGui->getRenderer()->setBackgroundColor(tgui::Color::White);
	PlayerGui->setPosition(1500, 790);
	PlayerGui->setTextSize(28);

	gui.add(waveCounter);
	gui.add(PlayerGui);
	gui.add(experienceBar);
	gui.add(waveText);


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
					player.Resetm_velocityY();
				}
				if (Event.key.code == sf::Keyboard::A || Event.key.code == sf::Keyboard::D) 
				{
					player.Resetm_velocityX();
				}
			}
			gui.handleEvent(Event);
		}

		
		PlayerDotMiniMap.setPosition(player.Renderer.GetPosition());

		//std::cout << std::endl << player.Renderer.GetPosition().x<<" " << player.Renderer.GetPosition().y;
		player.Control();
		player.Move(frameTime);

		
		waveText->setText("wave:" + std::to_string(waveNumber));
		waveCounter->setText("Wave start in:\n\n\t  " + std::to_string ((int)( 5 - timeBetwenWaves.getElapsedTime().asSeconds() )) );

		if (timeBetwenWaves.getElapsedTime().asSeconds() > 5 && !waveStarted) { // wave is starting
			waveStarted = true;
			waveCounter->setVisible(false);
			timeBetwenWaves.restart();
			
		}
		else if (timeBetwenWaves.getElapsedTime().asSeconds() < 5 && !waveStarted && !wavePrepared) { // wave havent started , mobs preparing
			int enemyUnitsPower = enemyUnitsPowerBase + waveNumber * enemyUnitsPowerMultipler;
			int enemyType;
			Bat* bat = new Bat(path[0], waveNumber);
			Knight* knight = new Knight(path[0], waveNumber);
			while (enemyUnitsPower > 0) {
				enemyType = randRange(randomNumberGenerator) + waveNumber;
				if (enemyType <= 60) {
					enemySpawnQueue.push_back(*bat);
					enemyUnitsPower -= 100 + waveNumber * 10;
				}
				else if (enemyType > 60) {
					enemySpawnQueue.push_back(*knight);
					enemyUnitsPower -= 100 + waveNumber * 10;
				}
			}
			wavePrepared = true;
			++waveNumber;
		}

			if (spawnPeriod.getElapsedTime().asSeconds() > 1.5f && !enemySpawnQueue.empty() && waveStarted) {
				enemiesLiving.push_back(enemySpawnQueue.back());
				enemySpawnQueue.pop_back();
				spawnPeriod.restart();
			}
		
			if (enemiesLiving.size() == 0 && waveStarted) {
				waveStarted = false;
				wavePrepared = false;
				waveCounter->setVisible(true);
			}

			for (auto& liveEnemy : enemiesLiving) {
				liveEnemy.FollowPath(frameTime);
			}
			//std::cout << waveStarted;

			experienceBar->setValue(player.GetExpPercentage());
			PlayerGui->setText("\n Level: " + std::to_string(player.GetLevel()) +
				"\t\n Attack: " + std::to_string(player.GetDamage())
				+ "\t\n Magic: 0  \t\n\n\t Exp\n");

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
		//window.draw(minimapBackground);
		

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
