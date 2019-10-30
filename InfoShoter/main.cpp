#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <TGUI/TGUI.hpp>
#include "screens.h"


int main()
{
	
	std::vector<cScreen*> Screens;
	int screen = 0;

	sf::RenderWindow window(sf::VideoMode(1024, 576), "InfoShoter");
	

	
	MenuScreen menuScreen;
	Screens.push_back(&menuScreen); //Add menuSC to Screens
	GameScreen gameScreen;
	Screens.push_back(&gameScreen); //Add menuSC to Screens

	while (screen >= 0) //main loop
	{
		screen = Screens[screen]->Run(window);
	}

	return 0;
}