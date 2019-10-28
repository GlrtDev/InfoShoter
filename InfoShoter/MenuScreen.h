#pragma once
//#include <iostream>
#include "cScreen.h"



class MenuScreen : public cScreen
{
public:
	MenuScreen(void);
	virtual int Run(sf::RenderWindow &App);
};