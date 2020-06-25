#pragma once

class PlayerInfoClass
{
public:
	int m_EasyLossCounter{}, m_EasyWinCounter{}, m_MediumLossCounter{}, m_MediumWinCounter{}, m_HardLossCounter{}, m_HardWinCounter{};
	std::string m_PlayerName;
public:
	void setPlayerInfo(std::string& name);
	int returnEasyLosses();
	int returnEasyWins();
	int returnMediumLosses();
	int returnMediumWins();
	int returnHardLosses();
	int returnHardWins();
	std::string returnName();
	void increaseEasyLosses();
	void increaseEasyWins();
	void increaseMediumLosses();
	void increaseMediumWins();
	void increaseHardLosses();
	void increaseHardWins();
	friend std::istream& operator>> (std::istream& input, PlayerInfoClass& data);
	friend std::ostream& operator<< (std::ostream& output, PlayerInfoClass& data);
	PlayerInfoClass() {};
	PlayerInfoClass(const PlayerInfoClass& toCopy)
	{
		m_PlayerName = toCopy.m_PlayerName;
		m_EasyLossCounter = toCopy.m_EasyLossCounter;
		m_EasyWinCounter = toCopy.m_EasyWinCounter;
		m_MediumLossCounter = toCopy.m_MediumLossCounter;
		m_MediumWinCounter = toCopy.m_MediumWinCounter;
		m_HardLossCounter = toCopy.m_HardLossCounter;
		m_HardWinCounter = toCopy.m_HardWinCounter;
	}
};