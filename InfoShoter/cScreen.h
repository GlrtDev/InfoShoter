#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
class cScreen //default screen class
{
public:
	virtual int Run(sf::RenderWindow &App) = 0;
};