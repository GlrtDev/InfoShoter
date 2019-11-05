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
