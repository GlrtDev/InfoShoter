#pragma once
#include <string>
#include <map>

 //tworze jako szablon �eby child klasy mia�y w�asne instancje statycznych p�l
class Gun 
{
protected:
	float damage;
	float fireSpeed;
	float accuracy;
	int ammo;

	int price;
	int ammoPrice;
	int level;

	std::string name;
	
public:
	virtual void shoot();
	virtual void reload();
};
