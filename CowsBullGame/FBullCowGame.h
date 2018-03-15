#pragma once
#include <string>

using FString = std::string;
using int32 = int; //we are only doing this in order to get used to using int32 instead of int which is required in unreal due to compiling to different platforms

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//the word class can be removed but then the scope is affected and we could not for example create a different enum 
enum class EGuessStatus //unreal likes to use E as starter for enum's
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {

public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTries() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	//bool CheckGuessValidity(FString) const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); //TODO make a more rich return value.
	
	//Provide a method for counting bulls and cows and increasing tries count
	FBullCowCount SubmitValidGuess(FString);

	//ignore on private just focus on public interface above
private:
	/* set in constructor code */
	int32 MyCurrentTry ;
	int32 MyMaxTries ;
	FString MyHiddenWord;
	bool bIsGameWon;
	bool IsIsogram(FString) const;


};