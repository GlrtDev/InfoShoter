#pragma once
#include <string>
#include <map>

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
	Gun();
	virtual void shoot();
	virtual void reload();
};
