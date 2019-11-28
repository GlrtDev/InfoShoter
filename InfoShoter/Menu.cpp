#include "Menu.h"

//void Menu::StartHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt)
//{
//	cScreen::goNext = true;
//}

void Menu::SignalHandler(tgui::Widget::Ptr widget, const std::string& signalName, const sf::String& buttonText)
{
	if (buttonText.toAnsiString() == "Next") {
		editBoxUsername->setVisible(false);
		nextButton->setVisible(false);
		listBox->setVisible(true);
		listBox->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
		startButton->setVisible(true);
		startButton->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
	}
	//std::cout << buttonText.toAnsiString();
	else if (buttonText.toAnsiString() == "Start")
	cScreen::goNext = true;
}

//void Menu::NextHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt)
//{
	
//}

Menu::Menu(tgui::Gui &gui)
{
	if (!texture1.loadFromFile("../Sprites/Female Student 1/femalestudent1.png"))
		std::cout << "chuj";
	if (!texture2.loadFromFile("../Sprites/Female Student 2/femalestudent2.png"))
		std::cout << "dupa";

	picture = tgui::Picture::create(texture1);
	picture->setSize({ "50%","100%" });
	picture->setPosition({ "50%","3%" });
	gui.add(picture);
	picture->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(4000));

	picture = tgui::Picture::create(texture2);
	picture->setSize({ "50%","100%" });
	picture->setPosition({ "0%","0%" });
	gui.add(picture);
	picture->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(4000));

	titleLabel = tgui::Label::create();
	titleLabel->setSize({ "66.67%", "12.5%" });
	titleLabel->setPosition({ "32%", "16.67%" });
	titleLabel->setText("InfoShoter");
	titleLabel->setTextSize(70);
	//titleLabel->setAutoSize(true);
	gui.add(titleLabel);
	titleLabel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
	// Create the login button

	editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize({ "25%", "12.5%" });
	editBoxUsername->setPosition({ "37.5%", "50%" });
	editBoxUsername->setDefaultText("Username");
	gui.add(editBoxUsername);
	editBoxUsername->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
	// Create the login button
	

	listBox = tgui::ListBox::create();
	//listBox->setRenderer(theme.getRenderer("ListBox"));
	listBox->setSize({ "20%", "30%" });
	listBox->setItemHeight(24);
	listBox->setPosition({ "40%", "40%" });
	listBox->addItem("Easy");
	listBox->addItem("Normal");
	listBox->addItem("Hard");
	gui.add(listBox);
	listBox->setVisible(false);

	nextButton = tgui::Button::create("Next");
	nextButton->setSize({ "20%", "10.67%" });
	nextButton->setPosition({ "40%", "70%" });
	gui.add(nextButton,"NextnextButton");
	nextButton->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));


	startButton = tgui::Button::create("Start");
	startButton->setSize({ "20%", "10.67%" });
	startButton->setPosition({ "40%", "70%" });
	gui.add(startButton, "StartstartButton");
	startButton->setVisible(false);
	

	//nextButton->connect("pressed", NextHandler, listBox, editBoxUsername, nextButton, startButton);
	nextButton->connect("pressed", &Menu::SignalHandler, this);
	startButton->connect("pressed", &Menu::SignalHandler, this); // THIS AT THE AND BECOZ MEMBER FUNCTIONS HAVE HIDDEN CLASS POINTER :)
}

void Menu::HideMenuGUI(tgui::Gui & gui)
{

}

void Menu::ShowMenuGUI(tgui::Gui & gui)
{

}

