#include "EventHandler.h"
//template <typename T>
void EventHandler::CollisionDetection(Player & player, tmx::ObjectGroup collisionLayer, sf::Time frameTime, std::vector<Enemy> &enemiesLiving)
{
	static sf::Time damagePeriod; 
	damagePeriod += frameTime;

	for (auto& object : collisionLayer.getObjects())
	{
		for (auto& point : player.m_boundingBox)
		{

			if (EventHandler::contains<tmx::Vector2f>(player.Renderer.GetPosition() - point, object.getPoints(), object.getPosition()))
			{
				player.WallCollision(frameTime);
				break;
			}
		}
	}

	for (auto enemy = enemiesLiving.begin(); enemy != enemiesLiving.end(); ++enemy) {
		
		bool collisionFinished = false;
		for (auto& point : player.m_boundingBox)
		{
			if(damagePeriod.asSeconds()> 0.05f)
			if (EventHandler::contains<sf::Vector2f>(player.Renderer.GetPosition() - point, enemy->GetboundingBox(), enemy->getPosition()))
			{
				damagePeriod = sf::Time::Zero;
				if (enemy->ReceiveDamage(player.GetDamage())) {
					//int index = std::distance(enemiesLiving.begin(), enemy);
					enemiesLiving.erase(enemy);
					//enemiesLiving.shrink_to_fit();
					
					//std::cout << index << "\t";
					collisionFinished = true;
				}
				break;
			}
			
		}
		if (collisionFinished == true) {
			std::cout << "break";
			break;
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
