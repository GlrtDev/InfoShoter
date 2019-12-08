#pragma once
#include <string>
#include <fstream>
typedef struct Score {
	std::string name;
	std::string difficulty;
	int wave;
	int playerLevel;
	int attack;
	int magic;
	int speed;

	friend void operator >> (std::fstream &file, Score &score)
	{
		file >> score.name >> score.difficulty >> score.wave >> score.playerLevel >> score.attack >> score.magic >> score.speed;
	}

	friend void operator << (std::fstream &file, Score &score )
	{
		file << score.name << ' ' << score.difficulty <<' '<< score.wave << ' ' << score.playerLevel << ' ' << score.attack << ' ' << score.magic << ' ' << score.speed;
	}

	friend void operator >> (Score &score ,std::fstream &file)
	{
		file << score.name << score.difficulty << score.wave << score.playerLevel << score.attack << score.magic << score.speed;
		/*score.name >> file;
		score.difficulty >> file;
		score.wave >> file;
		score.playerLevel >> file;
		score.attack >> file;
		score.magic >> file;
		score.speed >> file;*/
	}
};

