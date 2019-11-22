#include "EventHandler.h"

void EventHandler::CollisionDetection(Player & player, tmx::ObjectGroup collisionLayer, sf::Time frameTime)
{
	for (auto& object : collisionLayer.getObjects())
	{
		for (auto& point : player.boundingBox)
		{

			if (EventHandler::contains(player.Renderer.GetPosition() - point, object.getPoints(), object.getPosition()))
			{
				player.WallCollision(frameTime);
				break;
			}
		}
	}
}

std::queue<sf::Vector2f> EventHandler::initializePaths(std::queue<sf::Vector2f>* paths)
{
	paths[0].push(sf::Vector2f(782.f, 600.f));	
	paths[0].push(sf::Vector2f(179.f, 600.f));
	paths[0].push(sf::Vector2f(180.f, 600.f));
	paths[0].push(sf::Vector2f(180.f, 270.f));
	paths[0].push(sf::Vector2f(345.f, 270.f));
	paths[0].push(sf::Vector2f(345.f, 70.f));
	return *paths;
}
