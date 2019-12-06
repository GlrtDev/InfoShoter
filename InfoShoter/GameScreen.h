#pragma once
#pragma once
#include <iostream>
#include "cScreen.h"

class GameScreen : public cScreen
{
private:
	bool m_playing;
public:
	GameScreen(void);
	virtual int Run(sf::RenderWindow &App);
};