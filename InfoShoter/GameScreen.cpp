#include <iostream>
#include "GameScreen.h"

GameScreen::GameScreen(void)
{
	alpha_max = 3 * 255;
	alpha_div = 3;
	playing = false;
}

int GameScreen::Run(sf::RenderWindow & window)
{
	bool Running = true;
	sf::Event Event;
	tgui::Gui gui{ window };
	
	auto radioButton = tgui::RadioButton::create();
	//radioButton->setRenderer(theme.getRenderer("RadioButton"));
	radioButton->setPosition(20, 140);
	radioButton->setText("Yep!");
	radioButton->setSize(25, 25);
	gui.add(radioButton);

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
