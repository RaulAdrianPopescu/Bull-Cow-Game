#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <map>
#include <vector>
#include <time.h>
#include <stdlib.h>



struct FBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};

enum class EInputStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Not_Letter,
	Not_Number,
	HelpText,
	QuitGame,
};


class FBullCowGame
{
public:

	FBullCowGame();
	int GetMaxTries();
	int GetCurrentTry();
	void GetHiddenWord(int DifficultySelected);
	int GetHiddenWordLength() const;
	bool IsGameWon();
	EInputStatus CheckInputValidity(std::string& PlayerInput);
	std::string PrintGameSummary();
	void GiveHint();
	void Reset();
	FBullCowCount SubmitValidGuess(std::string& Guess);

private:

	int MyCurrentTry;
	std::string MyHiddenWord;
	bool bGameWon;
	bool IsIsogram(const std::string& Guess) const;
	bool IsLowercase(const std::string& Guess) const;
	bool IsLettersOnly(const std::string& Guess) const;
};
