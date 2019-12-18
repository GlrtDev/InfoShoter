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

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "InfoShoter", sf::Style::Default); //sf::Style::Fullscreen 
	window.setVerticalSyncEnabled(true);

	
	MenuScreen menuScreen;
	Screens.push_back(&menuScreen); //Add menuSC to Screens
	GameScreen gameScreen;
	Screens.push_back(&gameScreen); //Add gameSC to Screens

	while (screen >= 0) //main loop
	{
		screen = Screens[screen]->Run(window);
	}

	return 0;
}