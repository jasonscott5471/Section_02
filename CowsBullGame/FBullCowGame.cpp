#include "FBullCowGame.h"
using int32 = int;

//test git push

FBullCowGame::FBullCowGame()
{
	//constructors
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTries() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const
{
	//return int32();
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{

	return bIsGameWon;
}
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "building";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bIsGameWon = false;
	
	return;
}




//bool FBullCowGame::CheckGuessValidity(FString) const
EGuessStatus FBullCowGame::CheckGuessValidity(FString myGuess) const
{
	//return false;
	//return EGuessStatus::OK; //TODO make actual check if error or valid
	
	//guess not isogram; NOT implemented yet
	if (false)
	{
		return EGuessStatus::Not_Isogram; //TODO write function
	}
	//guess not all lowercase
	else if (false)
	{
		return EGuessStatus::Not_Lowercase; //TODO write function

	}
	//guess length wrong - too short
	else if (myGuess.length() != GetHiddenWordLength()) //here we are using the GetHiddenWordLength method
	{
		return EGuessStatus::Wrong_Length;
	}

	//otherwise ok
	else 
	{
		return EGuessStatus::OK;
	}

}

//receives a valid guess increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;

	//setup a return variable:these are initialized to zero
	FBullCowCount BullCowCount;

	//loop through all letters in the hidden word
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++) 
	{
		//compare letters against the guess word
		for (int32 j = 0; j < HiddenWordLength; j++) 
		{
			//if they match then
			//if (Guess[i] == MyHiddenWord[i])
			if (Guess[j] == MyHiddenWord[i])
			{
				//if they are in the same place

				if (i==j)
				{
					//increment bulls
					BullCowCount.Bulls++;
				}
				else
				{
					//its a miss	
					BullCowCount.Cows++;

				}

			}
			}			
	}

	if (BullCowCount.Bulls == HiddenWordLength) {
		bIsGameWon = true;
		 
	}
	else { bIsGameWon = false; }

	return BullCowCount;
}
