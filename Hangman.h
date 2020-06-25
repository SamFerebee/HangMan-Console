#pragma once
#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include "PlayerInfo.h"


class HangmanClass
{
private:
	bool m_bIsOnePlayer;
	std::string m_AnswerWord;
	int m_difficulty;
	char m_charGuess;
	int m_wrongCounter;
	std::vector<char> m_AnswerRevealVec;
	bool m_Correct;
	std::vector<std::string> m_AnswerBank;
	std::vector<char> m_CorrectCharGuesses;
	std::vector<char>m_IncorrectCharGuesses;
	int m_TempEasyLossCounter, m_TempEasyWinCounter, m_TempMediumLossCounter, m_TempMediumWinCounter, m_TempHardLossCounter, m_TempHardWinCounter;
	PlayerInfoClass* thePlayer;
public:
	HangmanClass(PlayerInfoClass* incomingPlayer)
	{
		thePlayer = incomingPlayer;
	}
	void isOnePlayer();
	void setAnswerWordSinglePlayer();
	void setAnswerWordTwoPlayer();
	void setDifficulty();
	void getCharGuess();
	void setAnswerRevealVec();
	bool returnOnePlayer();
	std::string returnAnswerWord();
	void gameLoop();
	void checkGuess();
	void printAnswerRevealVec();
	void printHangman();
	void createAnswerBank();
	std::vector<std::string>& returnAnswerBank();
	int returnAnswerBankSize();
	void importAnswerBankFromFile();
	void pickAnswerWord();
	int returnWinCounter();
	int returnLossCounter();
	int returnDifficulty();
};

