#include "Menu.h"
//void Menu::StartHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt)
//{
//	cScreen::goNext = true;
//}
int Menu::m_difficultLevel = 1;
std::string Menu::m_name = "abc";
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
	else if (buttonText.toAnsiString() == "Start") {
		Menu::m_difficultLevel = listBox->getSelectedItemIndex();
		if (editBoxUsername->getText().toAnsiString() != "")
			Menu::m_name = editBoxUsername->getText().toAnsiString();
		else
			Menu::m_name = editBoxUsername->getDefaultText();
		cScreen::goNext = true;

	}
	else if (buttonText.toAnsiString() == "Help") {
		helpText->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, sf::milliseconds(500));
		helpCloseButton->showWithEffect(tgui::ShowAnimationType::SlideFromBottom, sf::milliseconds(500));
	}
	else if (buttonText.toAnsiString() == "X") {
		helpText->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, sf::milliseconds(500));
		helpCloseButton->hideWithEffect(tgui::ShowAnimationType::SlideToBottom, sf::milliseconds(500));
	}
}

//void Menu::NextHandler(tgui::ListBox::Ptr listBox, tgui::EditBox::Ptr username, tgui::Button::Ptr nextBtt, tgui::Button::Ptr stBtt)
//{
	
//}

Menu::Menu(tgui::Gui &gui)
{
	/*if (!texture1.loadFromFile("../Sprites/Female Student 1/femalestudent1.png"))
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
	picture->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(4000));*/

	titleLabel = tgui::Label::create();
	titleLabel->setSize({ "66.67%", "12.5%" });
	titleLabel->setPosition({ "32%", "16.67%" });
	titleLabel->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	titleLabel->setText("InfoShoter");
	titleLabel->setTextSize(115);
	titleLabel->getRenderer()->setTextColor(sf::Color(216, 123, 29, 255));
	//titleLabel->setAutoSize(true);
	gui.add(titleLabel);
	titleLabel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
	// Create the login button

	editBoxUsername = tgui::EditBox::create();
	editBoxUsername->setSize({ "25%", "12.5%" });
	editBoxUsername->setPosition({ "37.5%", "55%" });
	editBoxUsername->setDefaultText("PlayerName");
	editBoxUsername->setTextSize(38);
	editBoxUsername->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	gui.add(editBoxUsername);
	editBoxUsername->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));
	// Create the login button
	

	listBox = tgui::ListBox::create();
	//listBox->setRenderer(theme.getRenderer("ListBox"));
	listBox->setSize({ "20%", "12.7%" });
	listBox->setItemHeight(24);
	listBox->setPosition({ "40%", "55%" });
	listBox->addItem("\t\t\t   Easy");
	listBox->addItem("\t\t\t Normal");
	listBox->addItem("\t\t\t   Hard");
	listBox->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	listBox->getRenderer()->setSelectedBackgroundColor(sf::Color(216, 123, 29, 255));
	listBox->getRenderer()->setBackgroundColorHover(sf::Color::Black);
	listBox->getRenderer()->setTextColorHover(sf::Color::White);
	listBox->getRenderer()->setSelectedBackgroundColorHover(sf::Color(150, 70, 0, 255));
	listBox->setTextSize(38);
	listBox->setItemHeight(45);
	listBox->setSelectedItemByIndex(1);
	gui.add(listBox);
	listBox->setVisible(false);

	nextButton = tgui::Button::create("Next");
	nextButton->setSize({ "20%", "10.67%" });
	nextButton->setPosition({ "40%", "70%" });
	nextButton->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	nextButton->getRenderer()->setBorders(5);
	nextButton->setTextSize(48);
	gui.add(nextButton,"NextnextButton");
	nextButton->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(800));


	startButton = tgui::Button::create("Start");
	startButton->setSize({ "20%", "10.67%" });
	startButton->setPosition({ "40%", "70%" });
	startButton->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	startButton->setTextSize(48);
	startButton->getRenderer()->setBorders(5);
	gui.add(startButton, "StartstartButton");
	startButton->setVisible(false);

	helpButton = tgui::Button::create("Help");
	helpButton->setPosition({ "42.5%", "88%" });
	helpButton->setSize({ "15%", "8%" });
	helpButton->getRenderer()->setBorders(5);
	helpButton->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	helpButton->setTextSize(40);
	gui.add(helpButton);

	helpText = tgui::Label::create();
	helpText->setPosition({ "5%" , "5%" });
	helpText->setSize({ "90%" , "90%" });
	helpText->getRenderer()->setBackgroundColor(sf::Color(20, 20, 20, 230));
	helpText->getRenderer()->setBorders(8);
	helpText->getRenderer()->setTextOutlineThickness(2);
	helpText->getRenderer()->setTextColor(sf::Color(216, 123, 29, 255));
	helpText->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	helpText->setText("\n\n\n\n\t\t\t MOVE\t\t\t\t ATTACK\n\t\t[W] up\t\t\t\t[I] sword attack\n\t\t[S] down\t\t   [O] shot magic projectile\n\t\t[A] left\n\t\t[D] right"
		"\n\n\nYou have to defend your flower. Enemies can't hurt you. Kill them before they go to the flower.\n\n\t\t\t\tSometimes they drop some magic. Click [E] to equip that magic or [Q] to dismiss.\n\n"
	"When you kill enemy you got experience. After getting a certain number of Experience you can \t\t\t\t\t\t\tlevel up. Click [1] [2] or [3] to increase one of your attributes");
	helpText->setTextSize(35);
	helpText->setVisible(false);
	gui.add(helpText);

	helpCloseButton = tgui::Button::create("X");
	helpCloseButton->setPosition({ "10%", "10%" });
	helpCloseButton->setSize({ "4%", "5%" });
	helpCloseButton->getRenderer()->setBorders(5);
	helpCloseButton->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	helpCloseButton->setTextSize(48);
	helpCloseButton->setVisible(false);
	gui.add(helpCloseButton);
	//nextButton->connect("pressed", NextHandler, listBox, editBoxUsername, nextButton, startButton);

	nextButton->connect("pressed", &Menu::SignalHandler, this);
	startButton->connect("pressed", &Menu::SignalHandler, this); // THIS AT THE AND BECOZ MEMBER FUNCTIONS HAVE HIDDEN CLASS POINTER :)
	helpButton->connect("pressed", &Menu::SignalHandler, this);
	helpCloseButton->connect("pressed", &Menu::SignalHandler, this);
}

void Menu::HideMenuGUI(tgui::Gui & gui)
{

}

void Menu::ShowMenuGUI(tgui::Gui & gui)
{

}

