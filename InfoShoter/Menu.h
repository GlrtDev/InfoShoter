#pragma once
#include <TGUI/TGUI.hpp>
#include <iostream>
#include "MenuScreen.h"
#include<SFML/System/String.hpp>

class Menu 
{
private:
	sf::Texture texture1, texture2;
	tgui::Picture::Ptr picture;
	tgui::Label::Ptr titleLabel;
	tgui::EditBox::Ptr editBoxUsername;
	tgui::ListBox::Ptr listBox;
	tgui::Button::Ptr nextButton;
	tgui::Button::Ptr startButton;
	tgui::Button::Ptr helpButton;
	tgui::Button::Ptr helpCloseButton;
	tgui::Label::Ptr helpText;
public:
	void SignalHandler(tgui::Widget::Ptr widget, const std::string& signalName, const sf::String& buttonText);

	//void NextHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt);

	//void LoadMenuGUI(tgui::Gui &gui);

	void HideMenuGUI(tgui::Gui &gui);

	void ShowMenuGUI(tgui::Gui &gui);
	
	Menu(tgui::Gui &gui);
};