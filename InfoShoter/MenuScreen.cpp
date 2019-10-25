#include "MenuScreen.h"
#include <iostream>

MenuScreen::MenuScreen(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}

int MenuScreen::Run(sf::RenderWindow & window)
{
	bool Running = true;
	sf::Event Event;
	tgui::Gui gui{ window };
	
	try
	{
		Menu::LoadMenuGUI(gui);
	}
	catch (const tgui::Exception& e)
	{
		std::cerr << "Failed to load Menu: " << e.what() << std::endl;
		return 1;
	}

	while (Running)
	{
		//Verifying events
		while (window.pollEvent(Event))
		{
			// Window closed
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}

			gui.handleEvent(Event);
		}

		window.clear();
		gui.draw();
		window.display();
	}
	return (-1);
}
