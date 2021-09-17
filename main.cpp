

#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetValidGuess();
bool AskToPlayAgain();
int DifficultySelection();

FBullCowGame BCGame;

int main()
{
	PrintIntro();
	do
	{
		BCGame.Reset();
		BCGame.GetHiddenWord(DifficultySelection());
		std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
		PlayGame();
	} while (AskToPlayAgain() == true);

	return 0;
}

///// Loop for number of turns asking for guessses while the game
///// is NOT won and there are still tries remaining 
void PlayGame()
{
	while ((!BCGame.IsGameWon()) && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		BCGame.GiveHint();
		std::string Guess{ GetValidGuess() };

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

	}
}

///// introduce the game
void PrintIntro()
{
	std::cout << "     WELCOME TO BULLS AND COWS GAME\n";
	std::cout << "            A fun word game\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^\n" << std::endl;
	std::cout << "  Guess the right isogram and you win!\n\n";
	std::cout << " Useful commands: !help (brings up the helptext)\n";
	std::cout << "                  !quit (exits the game)\n\n";
	std::cout << std::endl;
}

///// Loop until the user gives a valid guess
///// TODO fix bug with Try 1 error without player giving any input
std::string GetValidGuess()
{
	std::string Guess;
	EInputStatus Status = EInputStatus::Invalid_Status;

	while (true)
	{
		int CurrentTry{ BCGame.GetCurrentTry() };
		int MaxTries{ BCGame.GetMaxTries() };

		std::cout << "Try " << CurrentTry << " of " << MaxTries << ". What is your guess? ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckInputValidity(Guess);
		switch (Status)
		{
		case EInputStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;

		case EInputStatus::Not_Letter:
			std::cout << "Please use letters only.\n\n";
			break;

		case EInputStatus::Not_Lowercase:
			std::cout << "Please make sure all the characters are lowercase.\n\n";
			break;

		case EInputStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;

		case EInputStatus::QuitGame:
			exit(EXIT_SUCCESS);

		case EInputStatus::HelpText:
			std::cout << "\nThe goal of the game is for you to find the right isogram. An isogram is a word which has no repeating letters.\n\n";
			std::cout << "Example: the word 'planet' has no repeating letters, therefore, it is an isogram.\n\n";
			std::cout << "Everytime you type a guess, the game will provide you the number of 'Bulls' and 'Cows'. 'Bulls' represent the\n";
			std::cout << "number of CORRECT letters which are in the RIGHT position, while 'Cows' represents the number of CORRECT letters\n";
			std::cout << "which are in the WRONG position....let's hope you have a...bulls eye for these things ;)\n";
			std::cout << "(Please don't quit the game, this is the only bad pun that's in...promise.)\n\n";
			break;

		default:
			return Guess;
		}
	}
}

///// Ask player if they want to play again
bool AskToPlayAgain()
{
	std::cout << BCGame.PrintGameSummary();
	std::cout << "\n\nDo you want to play again?(y/n) ";
	std::string Response = "";
	getline(std::cin, Response);
	std::cout << std::endl << std::endl;

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

int DifficultySelection()
{
	EInputStatus Status = EInputStatus::Invalid_Status;

	do
	{
		std::cout << "How long would you like the word to be? (MIN: 3    MAX: 17) ";
		std::string DifficultySelected;
		std::cin >> DifficultySelected;
		std::cout << std::endl;

		Status = BCGame.CheckInputValidity(DifficultySelected);
		switch (Status)
		{
		case EInputStatus::HelpText:
			std::cout << "\nThe goal of the game is for you to find the right isogram. An isogram is a word which has no repeating letters.\n\n";
			std::cout << "Example: the word 'planet' has no repeating letters, therefore, it is an isogram.\n\n";
			std::cout << "Everytime you type a guess, the game will provide you the number of 'Bulls' and 'Cows'. 'Bulls' represent the\n";
			std::cout << "number of CORRECT letters which are in the RIGHT position, while 'Cows' represents the number of CORRECT letters\n";
			std::cout << "which are in the WRONG position....let's hope you have a...bulls eye for these things ;)\n";
			std::cout << "(Please don't quit the game, this is the only bad pun that's in...promise.)\n\n";
			break;

		case EInputStatus::Not_Number:
			std::cout << "Please enter a number.\n\n";
			break;

		case EInputStatus::QuitGame:
			exit(EXIT_SUCCESS);

		default:
			int DiffInt = stoi(DifficultySelected);
			return DiffInt;
		}
	} while (Status != EInputStatus::OK);
}