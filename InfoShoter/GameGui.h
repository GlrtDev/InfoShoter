#pragma once
#include <TGUI/TGUI.hpp>
#include <string>
#include "Player.h"
#include <fstream>
#include <sstream>

class GameGui
{
private:
	tgui::Label::Ptr 
		m_waveText, m_waveCounter, m_playerMainGui, m_levelUpHelp, m_magicGui,
		m_magicIconBG, m_lootMagicGui, m_gameOverText,m_gameOverTitle,m_quitGameScreen;
	tgui::ProgressBar::Ptr m_experienceBar, m_magicReloadFilm, m_manaBar;
	tgui::Picture::Ptr m_magicIcon;
	Player* m_player;
	const sf::Clock* m_timeBetweenWaves;
	const int* m_waveNumber;
	sf::Time* m_frameTime;
	bool* m_isGameLost;
	Score m_highScore;
	std::fstream m_scoreDataFile;
	enum Gamestate {Quit = -1 , Menu = 0 , Game = 1} m_gamestate;
public:
	GameGui(tgui::Gui &gui, Player* player, sf::Clock* timeBetwenWaves, int* waveNumber, sf::Time* frameTime, bool* isGameLost);
	~GameGui();
	void Update();
	void HideCounter();
	void ShowCounter();
	void ShowLevelUpHelp();
	void HideLevelUpHelp();
	int StateMonitor();

};

