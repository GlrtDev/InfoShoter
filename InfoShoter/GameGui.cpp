#include "GameGui.h"
#include <sstream>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}

GameGui::GameGui(tgui::Gui &gui, Player* player,sf::Clock* timeBetweenWaves, int* waveNumber, sf::Time* frameTime) : m_frameTime(frameTime), m_player(player), m_timeBetweenWaves(timeBetweenWaves), m_waveNumber(waveNumber)
{
	m_waveText = tgui::Label::create();
	m_waveText->getRenderer()->setFont(tgui::Font::Font("../assets/IMMORTAL.ttf"));
	m_waveText->getRenderer()->setBorders(5);
	m_waveText->getRenderer()->setBackgroundColor(tgui::Color::White);
	m_waveText->setPosition(1670, 780);
	m_waveText->setTextSize(28);

	m_waveCounter = tgui::Label::create();
	m_waveCounter->getRenderer()->setFont(tgui::Font::Font("../assets/KarmaFuture.ttf"));
	m_waveCounter->getRenderer()->setTextColor(tgui::Color::Red);
	m_waveCounter->getRenderer()->setTextOutlineThickness(1);
	m_waveCounter->getRenderer()->setTextOutlineColor(tgui::Color::Black);
	m_waveCounter->setPosition(720, 450);
	m_waveCounter->setTextSize(68);

	m_experienceBar = tgui::ProgressBar::create();
	m_experienceBar->setPosition(1620, 1015);
	m_experienceBar->setSize(200, 20);
	m_experienceBar->getRenderer()->setBorders(3);
	m_experienceBar->getRenderer()->setFillColor(sf::Color(201, 129, 60, 200));

	m_playerMainGui = tgui::Label::create();
	m_playerMainGui->getRenderer()->setFont(tgui::Font::Font("../assets/IMMORTAL.ttf"));
	m_playerMainGui->getRenderer()->setTextColor(tgui::Color::Black);
	m_playerMainGui->getRenderer()->setBorders(5);
	m_playerMainGui->getRenderer()->setBackgroundColor(tgui::Color::White);
	m_playerMainGui->setPosition(1600, 790);
	m_playerMainGui->setTextSize(28);

	m_magicGui = tgui::Label::create();
	m_magicGui->getRenderer()->setFont(tgui::Font::Font("../assets/IMMORTAL.ttf"));
	m_magicGui->getRenderer()->setTextColor(tgui::Color::Black);
	m_magicGui->getRenderer()->setBorders(5);
	m_magicGui->getRenderer()->setBackgroundColor(tgui::Color::White);
	m_magicGui->setPosition(1170, 895);
	m_magicGui->setTextSize(28);

	//m_magicIcon = player->GetCurrentMagic()->GetIcon();
	m_magicIcon = tgui::Picture::create();
	m_magicIcon->setPosition(1220, 950);
	m_magicIcon->setSize(75.f, 75.f);

	m_magicReloadFilm = tgui::ProgressBar::create();
	m_magicReloadFilm->setFillDirection(tgui::ProgressBar::FillDirection::TopToBottom);
	m_magicReloadFilm->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 0));
	m_magicReloadFilm->getRenderer()->setFillColor(sf::Color(0, 0, 0, 255));
	m_magicReloadFilm->getRenderer()->setOpacity(0.9f);
	m_magicReloadFilm->setPosition(1220, 950);
	m_magicReloadFilm->setSize(75.f, 75.f);
	m_magicReloadFilm->setValue(0);

	m_magicIconBG = tgui::Label::create();
	m_magicIconBG->setPosition(1215, 950);
	m_magicIconBG->getRenderer()->setBorders(3);
	m_magicIconBG->setTextSize(55);
	m_magicIconBG->getRenderer()->setBackgroundColor(sf::Color(10, 10, 10, 230));
	m_magicIconBG->setText("\t");

	m_lootMagicGui = tgui::Label::create();
	m_lootMagicGui->getRenderer()->setFont(tgui::Font::Font("../assets/IMMORTAL.ttf"));
	m_lootMagicGui->getRenderer()->setTextColor(tgui::Color::Black);
	m_lootMagicGui->getRenderer()->setBorders(5);
	m_lootMagicGui->getRenderer()->setBackgroundColor(tgui::Color::White);
	m_lootMagicGui->setPosition(1170, 695);
	m_lootMagicGui->setTextSize(28);

	m_manaBar = tgui::ProgressBar::create();
	m_manaBar->getRenderer()->setFillColor(sf::Color(0, 50, 200, 255));
	m_manaBar->getRenderer()->setBackgroundColor(sf::Color(0, 0, 20, 255));
	m_manaBar->setPosition(1190, 857);
	m_manaBar->setTextSize(18);
	m_manaBar->setSize(300, 35);

	gui.add(m_waveCounter);
	gui.add(m_playerMainGui);
	gui.add(m_experienceBar);
	gui.add(m_waveText);
	gui.add(m_magicGui);
	gui.add(m_magicIconBG);
	gui.add(m_magicIcon);
	gui.add(m_magicReloadFilm);
	gui.add(m_lootMagicGui);
	gui.add(m_manaBar);

	m_levelUpHelp = tgui::Label::create();
	m_levelUpHelp->getRenderer()->setFont(tgui::Font::Font("../assets/IMMORTAL.ttf"));
	m_levelUpHelp->setTextSize(25);
	m_levelUpHelp->getRenderer()->setBorders(3);
	m_levelUpHelp->getRenderer()->setBackgroundColor(tgui::Color(201, 129, 60, 200));
	//m_levelUpHelp->setText("Level Up!\nSkill Points: 0\n  Click:\n1 for attack\n2 for magic\n3 for speed");
	m_levelUpHelp->setPosition(1615, 560);
	//m_levelUpHelp
	gui.add(m_levelUpHelp);
}


GameGui::~GameGui()
{
}

void GameGui::Update()
{
	m_waveText->setText("wave:" + std::to_string(*m_waveNumber));
	m_waveCounter->setText("Wave start in\n\n\t\t\t" + std::to_string((int)(5 - m_timeBetweenWaves->getElapsedTime().asSeconds())));

	m_experienceBar->setValue(m_player->GetExpPercentage());
	
	m_playerMainGui->setText("\n   Level: " + std::to_string(m_player->GetLevel()) +
		"\t\n   Attack: " + std::to_string(m_player->GetDamage()) +
		"\t\n   Magic: " + std::to_string(m_player->GetMagicPower()) +
		"\t\n   Speed: " + std::to_string(m_player->GetSpeed()) +
		"\n\t  Exp\n");

	//TO DO this is uncool and ugly
	Magic* magic = m_player->GetCurrentMagic();
	if (magic != nullptr) {
		m_magicIcon->getRenderer()->setTexture(magic->GetIconTexture());
		m_magicGui->setVisible(true);
		m_magicIcon->setVisible(true);
		m_magicIconBG->setVisible(true);
		m_magicReloadFilm->setVisible(true);
		m_manaBar->setVisible(true);
		m_magicGui->setText(" " + magic->GetName() +
			" \n\t\t\t Damage: " + to_string_with_precision(magic->GetDamage(), 1) +
			" \n\t\t\t Speed: " + to_string_with_precision(magic->GetSpeed(), 1) +
			" \n\t\t\t Mana Cost: " + std::to_string(magic->GetManaCost()));
		m_magicReloadFilm->setValue(magic->CalculateRecharge(*m_frameTime));
		m_manaBar->setText("Mana: " + to_string_with_precision(m_player->GetMana(), 1));
		m_manaBar->setValue(m_player->GetManaPercentage());
	}
	else {
		m_magicGui->setVisible(false);
		m_magicIcon->setVisible(false);
		m_magicIconBG->setVisible(false);
		m_magicReloadFilm->setVisible(false);
		m_manaBar->setVisible(false);
	}

	Magic* lootMagic = m_player->GetEquipableMagic();
	if (lootMagic != nullptr) {
		m_lootMagicGui->setVisible(true);
		m_lootMagicGui->setText("\t NEW MAGIC FOUND!"
			" \n\t\t\t| Damage: " + to_string_with_precision(lootMagic->GetDamage(), 1) +
			" \n[E] equip   | Speed: " + to_string_with_precision(lootMagic->GetSpeed(), 1) +
			" \n[Q] dismiss | Mana Cost: " + std::to_string(lootMagic->GetManaCost()));
	}
	else {
		m_lootMagicGui->setVisible(false);
	}
	if (m_player->GetSkillpoints()) {
		m_levelUpHelp->setText("  Level Up!\n Skill Points: " 
			+ std::to_string(m_player->GetSkillpoints()) 
			+ " \n     Click:\n [1] for attack\n [2] for magic\n [3] for speed");
		ShowLevelUpHelp();
	}
	else
		HideLevelUpHelp();
}

void GameGui::HideCounter()
{
	m_waveCounter->setVisible(false);
}

void GameGui::ShowCounter()
{
	m_waveCounter->setVisible(true);
}

void GameGui::ShowLevelUpHelp()
{
	m_levelUpHelp->setVisible(true);
}

void GameGui::HideLevelUpHelp()
{
	m_levelUpHelp->setVisible(false);
}
