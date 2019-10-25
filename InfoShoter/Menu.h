#pragma once
#include <TGUI/TGUI.hpp>
#include <iostream>

namespace Menu 
{


	void StartHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt);

	void NextHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt);

	void LoadMenuGUI(tgui::Gui &gui);

	void HideMenuGUI(tgui::Gui &gui);

	void ShowMenuGUI(tgui::Gui &gui);
}