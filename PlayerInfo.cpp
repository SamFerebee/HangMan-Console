#include "Hangman.h"
#include "PlayerInfo.h"
#include <limits>


void PlayerInfoClass::setPlayerInfo(std::string& name)
{
	m_PlayerName = name;
	m_EasyLossCounter = 0;
	m_EasyWinCounter = 0; 
	m_MediumLossCounter = 0; 
	m_MediumWinCounter = 0;
	m_HardLossCounter = 0;
	m_HardWinCounter = 0;
}

int PlayerInfoClass::returnEasyLosses() { return m_EasyLossCounter; }
int PlayerInfoClass::returnEasyWins() { return m_EasyWinCounter; }
int PlayerInfoClass::returnMediumLosses() { return m_MediumLossCounter; }
int PlayerInfoClass::returnMediumWins() { return m_MediumWinCounter; }
int PlayerInfoClass::returnHardLosses() { return m_HardLossCounter; }
int PlayerInfoClass::returnHardWins() { return m_HardWinCounter; }
std::string PlayerInfoClass::returnName() { return m_PlayerName; }

void PlayerInfoClass::increaseEasyLosses() { m_EasyLossCounter++; }
void PlayerInfoClass::increaseEasyWins() { m_EasyWinCounter++; }
void PlayerInfoClass::increaseMediumLosses() { m_MediumLossCounter++; }
void PlayerInfoClass::increaseMediumWins() { m_MediumWinCounter++; }
void PlayerInfoClass::increaseHardLosses() { m_HardLossCounter++; }
void PlayerInfoClass::increaseHardWins() { m_HardWinCounter++; }

std::istream& operator>> (std::istream& input, PlayerInfoClass& data)
{
	std::getline(input, data.m_PlayerName, '|');
	input >> data.m_EasyWinCounter >> data.m_EasyLossCounter >> data.m_MediumWinCounter >> data.m_MediumLossCounter >> data.m_HardWinCounter >> data.m_HardLossCounter;
	input.ignore(32767, '\n');
	return input;
}

std::ostream& operator<< (std::ostream& output, PlayerInfoClass& data)
{
	output << data.m_PlayerName << '|' << ' ' << data.m_EasyWinCounter << ' ' << data.m_EasyLossCounter << ' ' << data.m_MediumWinCounter << ' '
		<< data.m_MediumLossCounter << ' ' << data.m_HardWinCounter << ' ' << data.m_HardLossCounter << '\n';
	return output;
}