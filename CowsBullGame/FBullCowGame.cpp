#include "FBullCowGame.h"
#include <map>
#define TMap std::map //doing this until we wire up for real in unreal. This is essentially use the TMap word but connecting to our own library which is std

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

	const FString HIDDEN_WORD = "building"; //remember this word MUST be an isogram
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
	if (!IsIsogram(myGuess))
	{
		return EGuessStatus::Not_Isogram; //TODO write function
	}
	//guess not all lowercase
	//else if (false)
	else if (!IsLowerCase(myGuess))
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

bool FBullCowGame::IsIsogram(FString Word) const
{
	//consider 0 and 1 length as isogram
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; //setup our map

	for (auto Letter : Word)   // remember : stands for "in" . So this will loop through all letters in variable Word
								// auto is synomonous in C++ as is object in VB; ie compiler figures out what is appropriate
								// auto should only be used in private declarations section or is recommended by tutor


	{
		Letter = tolower(Letter); //convert so we can do like comparison even if user has inputted upper and lower case letters
		//loop through all the letters

		if (LetterSeen[Letter]) {//if letter in the map
			return false; //not isogram
		}
		else {
			LetterSeen[Letter] = true; //add letter to the map
		}
		
	}
	return true;

}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	TMap<char, bool> LetterSeen; //setup our map

	for (auto Letter : Word)
	{
		if (isupper(Letter) )
		{ 
			return false; 
		}
		
	}

	return true;
}
