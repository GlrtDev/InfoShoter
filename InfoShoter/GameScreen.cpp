#include <string>
#include <math.h>
#include <random>

#include "GameScreen.h"
#include "Menu.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window.hpp>
#include "SFMLOrthogonalLayer.hpp"

#include <tmxlite/Map.hpp>

#include "Player.h"
#include "GameGui.h"
#include "Bat.h"
#include "Knight.h"
#include "Roque.h"
#include "BlobMinion.h"
#include "BlobSlime.h"
#include "Goblin.h"
#include "EventHandler.h"
#include <vector>
GameScreen::GameScreen(void) : m_playing(true) {};

int GameScreen::Run(sf::RenderWindow &window) {
	m_playing = true;
	std::queue<sf::Vector2f> path[3];
	EventHandler::initializePaths(path);
	const sf::Vector2f flowerPosition(660.f, 470.f);
	sf::View view;
	view.setViewport(sf::FloatRect(0.f, 0.f, 2.25f, 4.f)); // 9:16
	sf::View miniMap;
	miniMap.setViewport(sf::FloatRect(0.f, 0.75f, 0.25f, 0.25f)); // 9:16
	const sf::Vector2f cameraCorrection(310.f, 400.f);
	bool gameHasEnded = false;
	bool paused = false;
	bool Running = true;
	sf::Event Event;
	tgui::Gui gui{ window };

	tmx::Map map;
	map.load("../assets/Level1TileMap.tmx");

	MapLayer groundLayer(map, 0);
	MapLayer upperGroundLayer(map, 1);
	MapLayer decorativeLayer(map, 2);
	MapLayer animatedLayer(map, 3);
	tmx::ObjectGroup collisionLayer;
	/*tmx::ObjectGroup collisionLayer;*/
	int i = 1;
	for (auto &layer : map.getLayers()) { // set layer for collision handle
		if (layer->getType() == tmx::Layer::Type::Object) {
			collisionLayer = layer->getLayerAs<tmx::ObjectGroup>();
			std::cout << "\nleyer " << i << " is a collision layer\n";
			break;
		}
		else {
			std::cout << "\nleyer " << i << " is not collision layer\n";
			i++;
		}
	}

	sf::Clock spawnPeriod;
	sf::Clock timeBetwenWaves;
	sf::Clock globalClock;
	sf::Clock frameClock;
	sf::Time frameTime;
	sf::Time timeElapsed = sf::Time::Zero;

	const sf::Vector2f startPosition(350.f, 300.f);
	Player player(startPosition, Menu::m_difficultLevel ,Menu::m_name);

	// TO DO, make separate class from this
	// Enemy::InitialLoad();
	std::vector<Enemy> enemiesLiving;
	std::vector<Enemy> enemySpawnQueue;
	enemiesLiving.clear(); enemySpawnQueue.clear();
	bool waveStarted = false;
	bool wavePrepared = false;
	int waveNumber = 0;
	int enemyUnitsPowerBase = 500;
	int enemyUnitsPowerMultipler = 100;
	std::default_random_engine randomNumberGenerator;
	std::uniform_int_distribution<int> randRange(1, 100);

	GameGui gameGui(gui, &player, &timeBetwenWaves, &waveNumber, &frameTime, &gameHasEnded);

	while (Running) {
		// Verifying events
		while (window.pollEvent(Event)) {
			// Window closed
			if (Event.type == sf::Event::Closed) {
				return (-1);
			}

			if (Event.type == sf::Event::KeyReleased) {
				if (Event.key.code == sf::Keyboard::W ||
					Event.key.code == sf::Keyboard::S) {
					player.Resetm_velocityY();
				}
				if (Event.key.code == sf::Keyboard::A ||
					Event.key.code == sf::Keyboard::D) {
					player.Resetm_velocityX();
				}
				if (Event.key.code == sf::Keyboard::P)
					paused = !paused;
			}
			gui.handleEvent(Event);
		}
		frameTime = frameClock.restart();
		if (m_playing && !paused) {
			view.setCenter(player.Renderer.GetPosition() + cameraCorrection);
			miniMap.setCenter(player.Renderer.GetPosition());
			// std::cout << std::endl << player.Renderer.GetPosition().x<<" " <<
			// player.Renderer.GetPosition().y;
			player.Control();
			player.Move(frameTime);
			player.Update(frameTime);

			if (timeBetwenWaves.getElapsedTime().asSeconds() > 5 &&
				!waveStarted) { // wave is starting
				waveStarted = true;
				gameGui.HideCounter();
				timeBetwenWaves.restart();
			}
			else if (timeBetwenWaves.getElapsedTime().asSeconds() < 5 &&
				!waveStarted &&
				!wavePrepared) { // wave havent started , mobs preparing
				++waveNumber;
				int enemyUnitsPower =
					enemyUnitsPowerBase + waveNumber * enemyUnitsPowerMultipler;
				int enemyType;
				int pathNumber = (waveNumber / 10) % 3;
				Bat *bat = new Bat(path[pathNumber], waveNumber);
				Knight *knight = new Knight(path[pathNumber], waveNumber);
				Goblin *goblin = new Goblin(path[pathNumber], waveNumber);
				Roque *roque = new Roque(path[pathNumber], waveNumber);
				BlobMinion *blobMinion = new BlobMinion(path[pathNumber], waveNumber);
				Enemy *blobSlime = new BlobSlime(path[pathNumber], waveNumber);
				while (enemyUnitsPower > 0) {
					enemyType = randRange(randomNumberGenerator) + 5 * waveNumber;
					if (enemyType <= 50) {
						enemySpawnQueue.push_back(*bat); // bat
						enemyUnitsPower -= 100 + waveNumber * 10;
					}
					else if (enemyType > 50 && enemyType <= 100) {
						enemySpawnQueue.push_back(*knight);
						enemyUnitsPower -= 100 + waveNumber * 10;
					}
					else if (enemyType > 100 && enemyType <= 150) {
						enemySpawnQueue.push_back(*goblin);
						enemyUnitsPower -= 100 + waveNumber * 10;
					}
					else if (enemyType > 150 && enemyType <= 200) {
						enemySpawnQueue.push_back(*roque);
						enemyUnitsPower -= 100 + waveNumber * 10;
					}
					else if (enemyType > 200 && enemyType <= 250) {
						enemySpawnQueue.push_back(*blobSlime);
						enemyUnitsPower -= 100 + waveNumber * 10;
					}
					else if (enemyType > 250 && enemyType <= 300) {
						enemySpawnQueue.push_back(*blobMinion);
						enemyUnitsPower -= 100 + waveNumber * 10;
					}
				}
				wavePrepared = true;
			}

			if (spawnPeriod.getElapsedTime().asSeconds() > 1.5f &&
				!enemySpawnQueue.empty() && waveStarted) {
				enemiesLiving.push_back(enemySpawnQueue.back());
				enemySpawnQueue.pop_back();
				spawnPeriod.restart();
			}

			if (enemiesLiving.size() == 0 && waveStarted) {
				waveStarted = false;
				wavePrepared = false;
				gameGui.ShowCounter();
			}

			for (auto &liveEnemy : enemiesLiving) {
				liveEnemy.FollowPath(frameTime, m_playing); //inside is method to checking if enemy touched flower
			}
			// std::cout << waveStarted;
			sf::Time duration = globalClock.getElapsedTime();
			animatedLayer.update(duration);
			// COLISION DETECTION START
			EventHandler::CollisionDetection(player, collisionLayer, frameTime,
				enemiesLiving); // walls collisions
								// COLLISION DETECT END
		}
		else if (m_playing && !paused){
			sf::Vector2f newPosition = view.getCenter();
			sf::Vector2f delta;
			timeElapsed += frameTime;
			delta.x = newPosition.x - flowerPosition.x; delta.y = newPosition.y - flowerPosition.y;
			if (fabs(delta.x) > 3.f && fabs(delta.y) > 3.f)
				newPosition = newPosition - delta * frameTime.asSeconds();
			else
				gameHasEnded = true;
			view.setCenter(newPosition);
		}
		else if ( paused )
		{ }

		gameGui.Update();
		int runningState = gameGui.StateMonitor();
		if (runningState != 1)
		{
			return runningState; //change game state
		}
		window.clear(sf::Color::Black);

		window.setView(view);
		window.draw(groundLayer);
		window.draw(decorativeLayer);
		player.DrawProjectilesTest(window, frameTime);
		player.Renderer.Draw(window, frameTime);

		window.draw(upperGroundLayer);

		for (auto &en : enemiesLiving)
			en.Draw(window, frameTime); // TODO can pass frame time once
		  // window.draw(animatedLayer);

		window.setView(miniMap);
		// window.draw(minimapBackground);

		window.draw(groundLayer);

		for (auto &en : enemiesLiving)
			en.DrawOnMinimap(window);
		player.Renderer.DrawOnMinimap(window,
			frameTime); // TODO:  do not do this like this
		gui.draw();
		// player.Renderer.Draw(window, frameTime);
		// window.draw(upperGroundLayer);
		window.display();
	}
	return (-1);
}
