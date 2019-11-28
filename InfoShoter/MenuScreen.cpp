#include "Menu.h"
#include <iostream>



MenuScreen::MenuScreen(void)
{
}

int MenuScreen::Run(sf::RenderWindow & window)
{
	bool Running = true;
	sf::Event Event;
	tgui::Gui gui{ window };
	Menu menu(gui);
	try
	{
		//menu.LoadMenuGUI(gui);
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
			if (cScreen::goNext)
			{
				cScreen::goNext = false;
				return 1;
			}
			if(cScreen::goPrevious){}
			gui.handleEvent(Event);
		}

		window.clear();
		gui.draw();
		window.display();
	}
	return (-1);
}
