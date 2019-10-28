#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
class cScreen //default screen class
{
public:
	static bool goNext;
	static bool goPrevious;
	virtual int Run(sf::RenderWindow &App) = 0;
};