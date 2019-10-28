#include "Menu.h"

void Menu::StartHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt)
{
	cScreen::goNext = true;
}

void Menu::NextHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt)
{

	username->setVisible(false);
	nextBtt->setVisible(false);
	listBox->setVisible(true);
	listBox->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
	stBtt->setVisible(true);
	stBtt->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
}

void Menu::LoadMenuGUI(tgui::Gui &gui)
{
	auto titleLabel = tgui::Label::create();
	titleLabel->setSize({ "66.67%", "12.5%" });
	titleLabel->setPosition({ "32%", "16.67%" });
	titleLabel->setText("InfoShoter");
	titleLabel->setTextSize(70);
	//titleLabel->setAutoSize(true);
	gui.add(titleLabel);
	titleLabel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
	// Create the login button

	auto editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize({ "66.67%", "12.5%" });
	editBoxUsername->setPosition({ "16.67%", "50%" });
	editBoxUsername->setDefaultText("Username");
	gui.add(editBoxUsername);
	editBoxUsername->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
	// Create the login button
	

	auto listBox = tgui::ListBox::create();
	//listBox->setRenderer(theme.getRenderer("ListBox"));
	listBox->setSize({ "20%", "30%" });
	listBox->setItemHeight(24);
	listBox->setPosition({ "40%", "40%" });
	listBox->addItem("Easy");
	listBox->addItem("Normal");
	listBox->addItem("Hard");
	gui.add(listBox);
	listBox->setVisible(false);

	// Call the login function when the button is pressed and pass the edit boxes that we created as parameters
	auto nextButton = tgui::Button::create("Next");
	nextButton->setSize({ "50%", "16.67%" });
	nextButton->setPosition({ "25%", "70%" });
	gui.add(nextButton,"NextnextButton");
	nextButton->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));


	auto startButton = tgui::Button::create("Start");
	startButton->setSize({ "20%", "16.67%" });
	startButton->setPosition({ "40%", "70%" });
	gui.add(startButton, "StartstartButton");
	startButton->setVisible(false);
	

	nextButton->connect("pressed", NextHandler, listBox, editBoxUsername, nextButton, startButton);
	startButton->connect("pressed", StartHandler, listBox, editBoxUsername, nextButton, startButton);
	
}

void Menu::HideMenuGUI(tgui::Gui & gui)
{

}

void Menu::ShowMenuGUI(tgui::Gui & gui)
{

}

