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

	int GetMaxTries(int) const;
	int GetCurrentTry() const;
	std::string GetHiddenWord(int);
	int GetHiddenWordLength() const;
	bool IsGameWon() const;
	EInputStatus CheckInputValidity(std::string) const;
	std::string PrintGameSummary();
	void GiveHint() const;

	void Reset();
	FBullCowCount SubmitValidGuess(std::string);


private:
	int MyCurrentTry;
	std::string MyHiddenWord;

	bool bGameWon;
	bool IsIsogram(std::string) const;
	bool IsLowercase(std::string) const;
	bool IsLettersOnly(std::string) const;
};