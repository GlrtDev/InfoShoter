#pragma once
#include <TGUI/TGUI.hpp>
#include <string>
#include "Player.h"
class GameGui
{
private:
	tgui::Label::Ptr m_waveText, m_waveCounter, m_playerMainGui, m_levelUpHelp, m_magicGui, m_magicIconBG;
	tgui::ProgressBar::Ptr m_experienceBar;
	tgui::Picture::Ptr m_magicIcon;
	Player* m_player;
	sf::Clock* m_timeBetweenWaves;
	int* m_waveNumber;
public:
	GameGui(tgui::Gui &gui, Player* player, sf::Clock* timeBetwenWaves, int* waveNumber);
	~GameGui();
	void Update();
	void HideCounter();
	void ShowCounter();
	void ShowLevelUpHelp();
	void HideLevelUpHelp();
};

