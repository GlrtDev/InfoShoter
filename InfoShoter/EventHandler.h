#pragma once
#include "SFML/Graphics.hpp"
#include "tmxlite/Map.hpp"
#include <vector>
#include <queue>
#include "Enemy.h"
#include "Player.h"
class EventHandler {
public:
	template<typename T>
	static bool contains(sf::Vector2f point, std::vector<T> object, T position)
	{
		//if (object.size() < 3) return false;

		//check if enough poly points
		//if (m_points.size() < 3) return false;

		//else raycast through points - assuming given point is in world coords
		
		unsigned int i, j;
		bool result = false;
		for (i = 0, j = object.size() - 1; i < object.size(); j = i++)
		{
			sf::Vector2f pointI = sf::Vector2f(object[i].x + position.x, object[i].y + position.y) ; // X D
			sf::Vector2f pointJ = sf::Vector2f(object[j].x + position.x, object[j].y + position.y);// X D

			//std::cout << pointI.x<< " ";

			if (((pointI.y > point.y) != (pointJ.y > point.y)) &&
				(point.x < (pointJ.x - pointI.x) * (point.y - pointI.y)
					/ (pointJ.y - pointI.y) + pointI.x))
				result = !result;
		}
		//std::cout << std::endl;
		return result;
	}
	static void CollisionDetection(Player& player, tmx::ObjectGroup collisionLayer,sf::Time frameTime, std::vector<Enemy> &enemiesLiving);
	static void initializePaths(std::queue<sf::Vector2f> *paths);
	
};