#pragma once
#include <iostream>
#include "cScreen.h"
#include "Menu.h"

class MenuScreen : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
public:
	MenuScreen(void);
	virtual int Run(sf::RenderWindow &App);
};