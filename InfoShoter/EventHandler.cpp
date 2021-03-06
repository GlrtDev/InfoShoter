#include "EventHandler.h"
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 10);

void EventHandler::CollisionDetection(Player & player, tmx::ObjectGroup collisionLayer, sf::Time frameTime, std::vector<Enemy> &enemiesLiving)
{
	static sf::Time damagePeriod; 
	damagePeriod += frameTime;
	
	//player wall collision
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

	//playersword enemy collision
	if(player.IsAttacking())
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
					generator.seed(frameTime.asMicroseconds() * 100);
					auto randomNumber = std::bind(distribution, generator);
					//std::cout << randomNumber() << std::endl;
					if (randomNumber() <= 2) {
						Magic* lootMagic = new Magic(enemy->GetLevel(), frameTime.asMicroseconds()* 100,player.GetMagicPower());
						player.SetEquipableMagic(lootMagic);
					}
					player.GainExp(enemy->GetExp());
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
	//enemy magic collision
	if (player.GetCurrentMagic() != nullptr) {
		std::vector<Projectile>* projectiles = player.GetCurrentMagic()->GetProjectiles();

		if (!(projectiles->empty())) {
			for (auto enemy = enemiesLiving.begin(); enemy != enemiesLiving.end(); ++enemy) {
				bool collisionFinished = false;
				for (auto projectile = projectiles->begin(); projectile != projectiles->end(); ++projectile) {
					if (EventHandler::contains<sf::Vector2f>(projectile->GetCollisionPoint(), enemy->GetboundingBox(), enemy->getPosition())) {
						if (enemy->ReceiveDamage(projectile->GetDamage())) {
							generator.seed(frameTime.asMicroseconds() * 100);
							auto randomNumber = std::bind(distribution, generator);
							if (randomNumber() <= 2) {
								Magic* lootMagic = new Magic(enemy->GetLevel(), frameTime.asMicroseconds() * 100, player.GetMagicPower());
								player.SetEquipableMagic(lootMagic);
							}
							player.GainExp(enemy->GetExp());
							enemiesLiving.erase(enemy);
						}
						projectiles->erase(projectile);
						collisionFinished = true;
						break;
					}
				}
				if (collisionFinished) break;
			}
		}
	}
}

void EventHandler::initializePaths(std::queue<sf::Vector2f>* paths)
{
	paths[0].push(sf::Vector2f(782.f, 600.f));	
	paths[0].push(sf::Vector2f(179.f, 600.f));
	paths[0].push(sf::Vector2f(180.f, 600.f));
	paths[0].push(sf::Vector2f(180.f, 270.f));
	paths[0].push(sf::Vector2f(345.f, 270.f));
	paths[0].push(sf::Vector2f(345.f, 70.f));

	paths[1].push(sf::Vector2f(1400.f, 680.f));
	paths[1].push(sf::Vector2f(1400.f, 760.f));
	paths[1].push(sf::Vector2f(1083.f, 760.f));
	paths[1].push(sf::Vector2f(1083.f, 121.f));
	paths[1].push(sf::Vector2f(737.f, 121.f));
	paths[1].push(sf::Vector2f(737.f, 409.f));
	paths[1].push(sf::Vector2f(453.f, 409.f));
	paths[1].push(sf::Vector2f(453.f, 276.f));
	paths[1].push(sf::Vector2f(363.f, 276.f));
	paths[1].push(sf::Vector2f(363.f, 76.f));

	paths[2].push(sf::Vector2f(880.f, 980.f));
	paths[2].push(sf::Vector2f(1083.f, 980.f));
	paths[2].push(sf::Vector2f(1083.f, 121.f));
	paths[2].push(sf::Vector2f(737.f, 121.f));
	paths[2].push(sf::Vector2f(737.f, 409.f));
	paths[2].push(sf::Vector2f(453.f, 409.f));
	paths[2].push(sf::Vector2f(453.f, 276.f));
	paths[2].push(sf::Vector2f(363.f, 276.f));
	paths[2].push(sf::Vector2f(363.f, 76.f));
}
