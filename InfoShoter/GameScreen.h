#pragma once
#pragma once
#include <iostream>
#include "cScreen.h"

class GameScreen : public cScreen
{
private:
	int alpha_max;
	int alpha_div;
	bool playing;
public:
	GameScreen(void);
	virtual int Run(sf::RenderWindow &App);
};