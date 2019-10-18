#pragma once
#include <string>
#include <map>

template <class> //tworze jako szablon ¿eby child klasy mia³y w³asne instancje statycznych pól
class Gun 
{
protected:
	float damage;
	float fireSpeed;
	float accuracy;
	int ammo;

	static int price;
	static int ammoPrice;
	static int level;

	//sprite sprite
	std::string name;
	
public:
	virtual shoot();
};
