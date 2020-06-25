#include "Hangman.h"
#include <iterator>
#include <fstream>

void HangmanClass::isOnePlayer()
{
	std::string answer;
	bool playerModeLoop{ true };
	while (playerModeLoop)
	{
		std::cout << "Singleplayer or twoplayer mode?: ";
		std::getline(std::cin, answer);
		if (answer == "Single" || answer == "single" || answer == "1" || answer == "1p" || answer == "Singleplayer" || answer == "singleplayer")
		{
			m_bIsOnePlayer = true;
			playerModeLoop = false;
		}
		else if (answer == "Two" || answer == "two" || answer == "2" || answer == "2p" || answer == "Twoplayer" || answer == "twoplayer")
		{
			m_bIsOnePlayer = false;
			playerModeLoop = false;
		}
	}
}

void HangmanClass::createAnswerBank()
{
	std::vector<std::string> answerBank;
	answerBank.reserve(5);
	switch (m_difficulty)
	{
	case 1:
		//	pick easy word
		answerBank.push_back("spot");
		answerBank.push_back("area");
		answerBank.push_back("cat");
		answerBank.push_back("park");
		answerBank.push_back("green");
		answerBank.push_back("hey");
		answerBank.push_back("easy");
		answerBank.push_back("yes");
		answerBank.push_back("red");
		answerBank.push_back("ball");
		break;
	case 2:
		//pick medium word
		answerBank.push_back("kayak");
		answerBank.push_back("guitar");
		answerBank.push_back("atomic");
		answerBank.push_back("brittle");
		answerBank.push_back("airplane");
		answerBank.push_back("scratch");
		answerBank.push_back("fox");
		answerBank.push_back("violet");
		answerBank.push_back("sushi");
		answerBank.push_back("joke");
		answerBank.push_back("strong");
		answerBank.push_back("apple");
		answerBank.push_back("orange");
		answerBank.push_back("steak");
		answerBank.push_back("sauce");
		break;
	case 3:
		//pick expert word
		answerBank.push_back("banana");
		answerBank.push_back("elephant");
		answerBank.push_back("zipper");
		answerBank.push_back("quiz");
		answerBank.push_back("rhythm");
		answerBank.push_back("ivy");
		answerBank.push_back("crocodile");
		answerBank.push_back("xenophobia");
		answerBank.push_back("abrupt");
		answerBank.push_back("impeachment");
		answerBank.push_back("absurd");
		answerBank.push_back("blizzard");
		answerBank.push_back("jazz");
		answerBank.push_back("jinx");
		answerBank.push_back("juicy");
		answerBank.push_back("galaxy");
		answerBank.push_back("pixel");
		answerBank.push_back("gnarly");
		answerBank.push_back("puzzle");
		answerBank.push_back("stymied");
		answerBank.push_back("strength");
		answerBank.push_back("luxury");
		answerBank.push_back("revolt");
		answerBank.push_back("sideways");
		answerBank.push_back("element");
		break;
	}
	m_AnswerBank = answerBank;
}

void HangmanClass::importAnswerBankFromFile()
{
	std::ifstream myFile ("answerbank.txt");
	std::vector<std::string> answerBank{};
	std::string line;
	std::ifstream inFile;
	inFile.open("answerbank.txt");
	while (inFile >> line)
	{
		answerBank.push_back(line);
	}
	inFile.close();
	m_AnswerBank = answerBank;
}

void HangmanClass::pickAnswerWord()
{
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	std::uniform_int_distribution answerBankNum{ 0, (static_cast<int>(m_AnswerBank.size()) - 1) };
	m_AnswerWord = m_AnswerBank[answerBankNum(mersenne)];
}

void HangmanClass::setAnswerWordSinglePlayer()
{
	setDifficulty();
	createAnswerBank();
	pickAnswerWord();
}

void HangmanClass::setAnswerWordTwoPlayer()
{
	std::cout << "Enter the answer word: ";
	std::string answerWord;
	std::getline(std::cin, answerWord);
	m_AnswerWord = answerWord;
}

void HangmanClass::setDifficulty()
{
	std::cout << "Set game difficulty (1-3): ";
	int difficulty;
	bool inputLoop{ true };
	while (inputLoop)
	{
		std::cin >> difficulty;
		if (difficulty < 1 || difficulty > 3)
		{
			std::cout << "Difficulty can only be between 1-3: ";
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		}
		else
		{
			std::cin.ignore(32767, '\n');
			inputLoop = false;
		}
	}
	m_difficulty = difficulty;
}

void HangmanClass::setAnswerRevealVec()
{
	for (int i = 0; i < m_AnswerWord.length(); ++i)
	{
		m_AnswerRevealVec.push_back('_');
	}
}

void HangmanClass::getCharGuess()
{
	std::string stringGuess;
	//char guess;
	bool charGuessLoop{ true };
	while (charGuessLoop && m_Correct != true && m_wrongCounter < 10)
	{
		std::cout << "Enter a character to guess: ";
		std::getline(std::cin, stringGuess);
		if (stringGuess.length() > 1)
		{
			std::cout << "Submit " << stringGuess << " as a guess? ";
			std::string stringGuessAnswer;
			bool stringGuessLoop{ true };
			while (stringGuessLoop)
			{
				std::getline(std::cin, stringGuessAnswer);
				if (stringGuessAnswer == "Yes" || stringGuessAnswer == "yes")
				{
					if (stringGuess == m_AnswerWord)
					{
						m_Correct = true;
						stringGuessLoop = false;
						charGuessLoop = false;
					}
					else
					{
						++m_wrongCounter;
						std::cout << stringGuess << " is not the correct answer.\n";
						printHangman();
						stringGuessLoop = false;
						charGuessLoop = false;
					}
				}
				else if (stringGuessAnswer == "No" || stringGuessAnswer == "no")
				{
					stringGuessLoop = false;
				}
				else
					std::cout << "You must enter yes or no: ";
			}
		}
		else
		{
			m_charGuess = stringGuess[0];
			checkGuess();
		}
	}
}

void HangmanClass::printAnswerRevealVec()
{
	for (int i = 0; i < m_AnswerWord.length(); ++i)
	{
		std::cout << m_AnswerRevealVec[i] << ' ';
	}
}

void HangmanClass::checkGuess()
{
	std::vector<int> foundElements;
	for (int i = 0; i < m_AnswerWord.length(); ++i)
	{
		if (m_AnswerWord[i] == m_charGuess)
			foundElements.push_back(i);
	}
	if (foundElements.size() == 0)
	{
		bool printBadGuess{ true };
		for (int i = 0; i < m_IncorrectCharGuesses.size(); ++i)
		{
			if (m_charGuess == m_IncorrectCharGuesses[i])
			{
				std::cout << "You already guessed " << m_charGuess << '\n';
				printBadGuess = false;
			}
		}
		if (printBadGuess)
		{
			++m_wrongCounter;
			m_IncorrectCharGuesses.push_back(m_charGuess);
			std::cout << "Incorrect guess.\n";
			printHangman();
		}
	}
	else
	{
		bool printGoodGuess{ true };
		for (int i = 0; i < m_CorrectCharGuesses.size(); ++i)
		{
			if (m_charGuess == m_CorrectCharGuesses[i])
			{
				std::cout << "You already guessed " << m_charGuess << '\n';
				printGoodGuess = false;
			}
		}
		if (printGoodGuess)
		{
			std::cout << "Good guess! The word is now: ";
			for (int i = 0; i < foundElements.size(); ++i)
			{
				m_AnswerRevealVec[foundElements[i]] = m_charGuess;
			}
			printAnswerRevealVec(); std::cout << '\n';
			m_CorrectCharGuesses.push_back(m_charGuess);
		}
	}
	///////check to see if user has completed word by seeing if any blanks _ remain
	auto ifCorrect = std::find(m_AnswerRevealVec.begin(), m_AnswerRevealVec.end(), '_');
	if (ifCorrect == m_AnswerRevealVec.end())
		m_Correct = true;
}

void HangmanClass::gameLoop()
{
	m_wrongCounter = 0;
	m_Correct = false;
	setAnswerRevealVec();
	std::cout << "The answer has "  << m_AnswerWord.length() << " characters in it.\n";
	printAnswerRevealVec();
	std::cout << '\n';
	while (m_wrongCounter < 10 && (m_Correct == false))
	{
		getCharGuess();
	}
	if (m_wrongCounter > 9)
	{
		std::cout << "You lose!\n";
		switch (m_difficulty)
		{
		case 1:
			thePlayer->increaseEasyLosses();
			break;
		case 2:
			thePlayer->increaseMediumLosses();
			break;
		case 3:
			thePlayer->increaseHardLosses();
			break;
		}
	}
	if (m_Correct == true)
	{
		std::cout << "You win!\n";
		switch (m_difficulty)
		{
		case 1:
			thePlayer->increaseEasyWins();
			break;
		case 2:
			thePlayer->increaseMediumWins();
			break;
		case 3:
			thePlayer->increaseHardWins();
			break;
		}
	}
}

void HangmanClass::printHangman()
{
	switch (m_wrongCounter)
	{
	case 1:
		std::cout << " O\n";
		break;
	case 2:
		std::cout << " O\n" << " |\n";
		break;
	case 3:
		std::cout << " O\n" << "\\|\n";
		break;
	case 4:
		std::cout << " O\n" << "\\|/" << '\n';
		break;
	case 5:
		std::cout << " O\n" << "\\|/" << '\n' << "/" << '\n';
		break;
	case 6:
		std::cout << " O\n" << "\\|/" << '\n' << "/" << "\\" << '\n';
		break;
	case 7:
		std::cout << " O\n" << "\\|/" << '\n' << "/" << "\\" << '\n' << "cough...\n";
		break;
	case 8:
		std::cout << " O\n" << "\\|/" << '\n' << "/" << "\\" << '\n' << "cough...cough...\n";
		break;
	case 9:
		std::cout << " O\n" << "\\|/" << '\n' << "/" << "\\" << '\n' << "cough...cough...cough...\n";
		break;
	case 10:
		std::cout << " O\n" << "\\|/" << '\n' << "/" << "\\" << '\n' << "cough...cough...cough...DEAD\n";
		std::cout << "The answer was " << m_AnswerWord << '\n';
		break;
	}
}


////////////////return functions

bool HangmanClass::returnOnePlayer()
{
	return m_bIsOnePlayer;
}

std::string HangmanClass::returnAnswerWord()
{
	return m_AnswerWord;
}

int HangmanClass::returnAnswerBankSize()
{
	return m_AnswerBank.size();
}

std::vector<std::string>& HangmanClass::returnAnswerBank()
{
	return m_AnswerBank;
}

int HangmanClass::returnLossCounter()
{
	switch (m_difficulty)
	{
	case 1:
		return m_TempEasyLossCounter;
	case 2:
		return m_TempMediumLossCounter;
	case 3:
		return m_TempHardLossCounter;
	}
}

int HangmanClass::returnWinCounter()
{
	switch (m_difficulty)
	{
	case 1:
		return m_TempEasyWinCounter;
	case 2:
		return m_TempMediumWinCounter;
	case 3:
		return m_TempHardWinCounter;
	}
}

int HangmanClass::returnDifficulty() { return m_difficulty; }