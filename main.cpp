#include "Hangman.h"
#include <fstream>
#include <memory>

void writeScoresToFile(std::vector<PlayerInfoClass>& playerInfoBank);
std::vector<PlayerInfoClass> createPlayerInfoBank();
void printRecords(std::vector<PlayerInfoClass>& playerBank);

int main()
{
	bool playGame{ true };
	std::cout << "Welcome To Sam's Hangman.";
	Sleep(800);
	system("CLS");
	bool isNewPlayer{ false };
	std::string userName;
	std::cout << "Enter your name: ";
	std::getline(std::cin, userName);
	PlayerInfoClass thePlayer;
	std::fstream inputFile; 
	inputFile.open("player_records.txt");
	std::vector<PlayerInfoClass> playerInfoBank;
	
	if (inputFile)
	{
		playerInfoBank = createPlayerInfoBank();
		auto result = std::find_if(playerInfoBank.begin(), playerInfoBank.end(),
			[userName](PlayerInfoClass& plyr) { return plyr.returnName() == userName; });

		if (result != playerInfoBank.end())
		{
			int elementNumber{ result - playerInfoBank.begin() };
			thePlayer = playerInfoBank[elementNumber];
		}
		else
		{
			thePlayer.setPlayerInfo(userName);
			isNewPlayer = true;
		}
	}
	else
	{
		isNewPlayer = true;
		thePlayer.setPlayerInfo(userName);
	}

	std::string recordViewAnswer;
	do
	{
		std::cout << "Would you like to view the record book? ";
		std::getline(std::cin, recordViewAnswer);
	} while (recordViewAnswer != "yes" && recordViewAnswer != "Yes" && recordViewAnswer != "no" && recordViewAnswer != "No");
	if (recordViewAnswer == "yes" || recordViewAnswer == "Yes")
	{
		if (inputFile)
		{
			system("CLS");
			printRecords(playerInfoBank);
			std::cout << "Press Enter when you are ready to proceed.\n";
			std::cin.get();
			system("CLS");
		}
		else
		{
			std::cout << "You have no records saved, start playing!\n";
			Sleep(1500); system("CLS");
		}
			
	}

	int gamesPlayedCounter = 0;
	PlayerInfoClass* playerPtr{ &thePlayer };
	while (playGame)
	{
		HangmanClass hangman(playerPtr);
		std::string answerWord;
		hangman.isOnePlayer();
		if (hangman.returnOnePlayer())
			hangman.setAnswerWordSinglePlayer();
		else
			hangman.setAnswerWordTwoPlayer();

		hangman.gameLoop();
		gamesPlayedCounter++;
		
		std::cout << "You have the following record: \n";
		std::string winOrWins{ "wins" };
		std::string lossOrLosses{ "losses" };
		if (thePlayer.returnEasyWins() == 1)
			winOrWins = "win";
		if (thePlayer.m_EasyLossCounter == 1)
			lossOrLosses = "loss";
		std::string winOrWinsMed{ "wins" };
		std::string lossOrLossesMed{ "losses" };
		if (thePlayer.m_MediumWinCounter == 1)
			winOrWinsMed = "win";
		if (thePlayer.m_EasyLossCounter == 1)
			lossOrLossesMed = "loss";
		std::string winOrWinsHard{ "wins" };
		std::string lossOrLossesHard{ "losses" };
		if (thePlayer.m_HardWinCounter == 1)
			winOrWinsHard = "win";
		if (thePlayer.m_HardLossCounter == 1)
			lossOrLossesHard = "loss";
		
		std::cout << thePlayer.returnEasyWins() << ' ' << winOrWins << " and " << thePlayer.returnEasyLosses() << ' ' << lossOrLosses << " on easy.\n";
		std::cout << thePlayer.returnMediumWins() << ' ' << winOrWinsMed << " and " << thePlayer.returnMediumLosses() << ' ' << lossOrLossesMed << " on medium.\n";
		std::cout << thePlayer.returnHardWins() << ' ' << winOrWinsHard << " and " << thePlayer.returnHardLosses() << ' ' << lossOrLossesHard << " on hard.\n";
		
		if (isNewPlayer == true && gamesPlayedCounter == 1)
			playerInfoBank.push_back(thePlayer);
		if (isNewPlayer == false)
		{
			int it;
			for (int i = 0; i < playerInfoBank.size(); ++i)
			{
				if (playerInfoBank[i].returnName() == userName)
					it = i;
			}
			playerInfoBank[it] = thePlayer;
		}

		///check to see if user wants to play again
		std::string playAgainAnswer;
		bool playAgainInputLoop{ true };
		while (playAgainInputLoop)
		{ 
			std::cout << "Would you like to play again? ";
			std::getline(std::cin, playAgainAnswer);
			if (playAgainAnswer == "No" || playAgainAnswer == "no")
			{
				std::cout << "Thanks for playing!";
				writeScoresToFile(playerInfoBank);
				playAgainInputLoop = false;
				playGame = false;
			}
			else if (playAgainAnswer == "Yes" || playAgainAnswer == "yes")
			{
				std::cout << "Starting a new game...\n"; Sleep(500);
				system("CLS");
				playAgainInputLoop = false;
			}
			else
				std::cout << "You must enter yes or no.\n";
		}
	}
	std::cin.get();
	return 0;
}


void writeScoresToFile(std::vector<PlayerInfoClass>& playerInfoBank)
{
	std::ofstream output;
	output.open("player_records.txt");
	for (int i = 0; i < playerInfoBank.size(); ++i)
	{
		output << playerInfoBank[i];
	}
	output.close();
}

std::vector<PlayerInfoClass> createPlayerInfoBank()
{
	std::vector<PlayerInfoClass> returnVector;
	std::ifstream inFile;
	inFile.open("player_records.txt");
	PlayerInfoClass thePlayerClass;
	while (inFile >> thePlayerClass)
	{
		returnVector.push_back(thePlayerClass);
	}
	inFile.close();
	return returnVector;
}

void printRecords(std::vector<PlayerInfoClass>& playerBank)
{
	for (int i = 0; i < playerBank.size(); ++i)
	{
		std::string winOrWins{ "wins" };
		std::string lossOrLosses{ "losses" };
		if (playerBank[i].returnEasyWins() == 1)
			winOrWins = "win";
		if (playerBank[i].m_EasyLossCounter == 1)
			lossOrLosses = "loss";
		std::string winOrWinsMed{ "wins" };
		std::string lossOrLossesMed{ "losses" };
		if (playerBank[i].m_MediumWinCounter == 1)
			winOrWinsMed = "win";
		if (playerBank[i].m_EasyLossCounter == 1)
			lossOrLossesMed = "loss";
		std::string winOrWinsHard{ "wins" };
		std::string lossOrLossesHard{ "losses" };
		if (playerBank[i].m_HardWinCounter == 1)
			winOrWinsHard = "win";
		if (playerBank[i].m_HardLossCounter == 1)
			lossOrLossesHard = "loss";

		std::cout << "Player name: " << playerBank[i].m_PlayerName << '\n';
		std::cout << playerBank[i].returnEasyWins() << ' ' << winOrWins << " and " << playerBank[i].returnEasyLosses() << ' ' << lossOrLosses << " on easy.\n";
		std::cout << playerBank[i].returnMediumWins() << ' ' << winOrWinsMed << " and " << playerBank[i].returnMediumLosses() << ' ' << lossOrLossesMed << " on medium.\n";
		std::cout << playerBank[i].returnHardWins() << ' ' << winOrWinsHard << " and " << playerBank[i].returnHardLosses() << ' ' << lossOrLossesHard << " on hard.\n\n";


		/*
		std::cout << "Player name: " << playerBank[i].returnName() << '\n' << playerBank[i].returnEasyWins() << " easy wins and " << playerBank[i].returnEasyLosses() << " easy losses\n";
		std::cout << playerBank[i].returnMediumWins() << " medium wins and " << playerBank[i].returnMediumLosses() << " losses\n";
		std::cout << playerBank[i].returnHardWins() << " hard wins and " << playerBank[i].returnHardLosses() << " losses\n\n";
		*/
	}
}