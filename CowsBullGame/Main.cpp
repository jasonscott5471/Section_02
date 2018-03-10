/*
This is the console executable that makes use of the BullCow class
This acts as the view in MVC pattern and is responsible for all user interactions.
For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//using FText as its used in unreal engine, along with FString
using FText = std::string;
using int32 = int;


//not good practice in c++ hence we are removing all namespace references
//using namespace std;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
FText PrintGuess(FText myGuess);
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game


int main()
{
	//ctrl+F5 to execute with debugging which keeps the console window page open
	
	//temp for testing

	//std::cout << BCGame.GetCurrentTries();


	//get a guess from the player
	FText Guess = "";
	bool bWantsToPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bWantsToPlayAgain = AskToPlayAgain();
	
	} 
	while (bWantsToPlayAgain == true);
	return 0;

}

void PrintIntro() 
{
	//constexpr int32 WORD_LENGTH = 5;
	//constexpr is used for static length variables

	std::cout << "Welcome to bulls and cows.\n";

	int32 HidWL = BCGame.GetHiddenWordLength();
	std::cout << "Can you guess the " << HidWL;
	//std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " X letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;

}
void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	std::cout << "MaxTries is:" << MaxTries << std::endl;


	constexpr int32 NUMBER_OF_TURNS = 5;
	//FText myGuess = "";

	//TODO change from FOR to WHILE loop once we are validating tries
	//for (int count = 1; count <= NUMBER_OF_TURNS; count++)
	for (int32 count = 1; count <= MaxTries; count++)
	{
		//GetGuessAndPrint();
		FText myGuess = GetValidGuess(); 

	
		//Submit valid guess to the game engine and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(myGuess);
	
		//Print number of bulls and cows

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " . Cows = " << BullCowCount.Cows << "\n\n";
		
	}
	//TODO add a game summary

}

//loop continuously until user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Guess = "";

	do {
		   int32 CurrentTry = BCGame.GetCurrentTries();

		   std::cout << "Try " << CurrentTry << ". Enter a guess: \n";
		   //cin >> Guess;
		   //get a guess from the player
		   

		   std::getline(std::cin, Guess);

		   //check validity of guess
		   //EGuessStatus GuessStatus = BCGame.CheckGuessValidity(Guess);
		   Status = BCGame.CheckGuessValidity(Guess);

		   switch (Status)
		   {
		   case EGuessStatus::OK:
			  // return "OK";
			   break;
		   case EGuessStatus::Not_Isogram:
			   std::cout << "Your guess word must not have repeating letters.\n";
			  // return "NotValid";
			   break;
		   case EGuessStatus::Wrong_Length:
			   std::cout << "Your guess word must be " << BCGame.GetHiddenWordLength() << " letter word.\n";
			  // return "NotValid";
			   break;
		   case EGuessStatus::Not_Lowercase:
			   std::cout << "Your guess word must be all lowercase letters.\n";
			  // return "NotValid";
			   break;
		   default:
			   //break;
			   //return Guess;
			   //assume guess is valid
			   break;
		   }

		   std::cout << std::endl;

	} while (Status != EGuessStatus::OK);
	return Guess;
}
FText PrintGuess(FText myGuess) {
	
	std::cout << std::endl;
	std::cout << "Your guess was \n" << myGuess << "\n";
	std::cout << std::endl;

	return myGuess;
	//return;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	//cout << Response[0];

	if (Response[0] == 'y' || Response[0] == 'Y')
	{
		std::cout << "Time to play again!\n";
		std::cout << std::endl;
		return true;

	}
	else
	{
		std::cout << "Game Over!";
		std::cout << std::endl;
		return false;
	}
	
	

	//return false;
}
