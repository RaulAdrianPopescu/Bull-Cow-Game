#pragma once

#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }


int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

std::string FBullCowGame::GetHiddenWord(int DifficultySelected)
{
	// Create vector of words, word size dependent on DifficultySelected, will return a random string from vector for HiddenWord
	std::ifstream FromIsogram("isograms.txt");
	std::string WordFromList;
	std::vector<std::string> SelectedWords;
	do
	{
		FromIsogram >> WordFromList;
		if (WordFromList.size() == DifficultySelected)
		{
			SelectedWords.push_back(WordFromList);
		}
		else { WordFromList.clear(); }
	} while (!FromIsogram.eof());
	// Close file and shrink vector to fit chosen words
	FromIsogram.close();
	SelectedWords.shrink_to_fit();

	// Return random value based on random index, which will be MyHiddenWord, then clear the vector of all its values
	srand(time(NULL));
	MyHiddenWord = SelectedWords[rand() % SelectedWords.size()];
	SelectedWords.clear();

	return MyHiddenWord;
}

int FBullCowGame::GetMaxTries(int) const
{
	std::map <int, int> WordLengthToMaxTries
	{
		{3, 3},
		{4, 5},
		{5, 6},
		{6, 8},
		{7, 9},
		{8, 11},
		{9, 12},
		{10, 15},
		{11, 16},
		{12, 18},
		{13, 21},
		{14, 22},
		{15, 24},
		{16, 25},
		{17, 27}
	};
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset()
{
	bGameWon = false;

	std::string MyHiddenWord{};
	MyCurrentTry = 1;
	return;
}


EInputStatus FBullCowGame::CheckInputValidity(std::string PlayerInput) const
{
	if (PlayerInput == "!help")
	{
		return EInputStatus::HelpText;
	}
	else if (PlayerInput == "!quit")
	{
		return EInputStatus::QuitGame;
	}
	else if (isalpha(PlayerInput[0]))
	{
		return EInputStatus::Not_Number;
	}
	else if (PlayerInput.length() != GetHiddenWordLength())
	{
		return EInputStatus::Wrong_Length;
	}
	else if (!IsLettersOnly(PlayerInput))
	{
		return EInputStatus::Not_Letter;
	}
	else if (!IsLowercase(PlayerInput))
	{
		return EInputStatus::Not_Lowercase;
	}
	else if (!IsIsogram(PlayerInput))
	{
		return EInputStatus::Not_Isogram;
	}
	else
	{
		return EInputStatus::OK;
	}
}

std::string FBullCowGame::PrintGameSummary()
{
	if (bGameWon == true)
	{
		return "CONGRATULATIONS! YOU WON!\n";
	}
	else
	{
		return "BETTER LUCK NEXT TIME :(\nThe hidden word was: " + MyHiddenWord;
	}
}

// Receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(std::string Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int WordLength = MyHiddenWord.length(); // Assuming same length as guess

	// Loop through all letters in the hidden word

	for (int MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// Compare letters against the guess
		for (int GChar = 0; GChar < WordLength; GChar++)
		{
			// If they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				// If they're in the same place
				if (MHWChar == GChar)
				{
					// Increment bulls
					BullCowCount.Bulls++;
				}
				else
				{
					// Increment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameWon = true;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(std::string Guess) const
{
	// Treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1) { return true; }

	std::map <char, bool> LetterSeen; // Setup our map
	for (auto Letter : Guess)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; }
		else { LetterSeen[Letter] = true; }
	}

	return true;
}

bool FBullCowGame::IsLowercase(std::string Guess) const
{
	for (auto Letter : Guess)
	{
		if (islower(Letter) == false) { return false; }
	}
	return true;
}

bool FBullCowGame::IsLettersOnly(std::string Guess) const
{
	for (auto Letter : Guess)
	{
		if (isalpha(Letter) == false) { return false; }
	}
	return true;
}

void FBullCowGame::GiveHint() const
{
	std::string FirstHiddenLetter{ MyHiddenWord[0] };
	std::string LastHiddenLetter{ MyHiddenWord[GetHiddenWordLength() - 1] };
	std::cout << "HINT: Your word begins with " << FirstHiddenLetter << " and ends in " << LastHiddenLetter << ".\n\n";

	return;
}