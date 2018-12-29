#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLenghtToMaxTries{ {4, 5}, {5, 5}, {6, 7}, {8, 9}, {9, 12}, {10, 14} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;
	
	int32 WordLength = GetHiddenWordLength();

	for (int32 MyHiddenWordChar = 0; MyHiddenWordChar < WordLength; MyHiddenWordChar++) 
	{
		for (int32 MyGuessChar = 0; MyGuessChar < WordLength; MyGuessChar++) 
		{
			if (Guess[MyGuessChar] == MyHiddenWord[MyHiddenWordChar])
			{
				if (MyHiddenWordChar == MyGuessChar)
				{
					BullCowCount.Bulls++;
				} 
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	} 
	else 
	{
		bGameIsWon = false;
	}
		
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter]) 
		{
			return false;
		} 
		else 
		{
			LetterSeen[Letter] = true;
		}
	}
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if(!islower(Letter)) 
		{
			return false;
		}
	}

	return true;
}

void FBullCowGame::Reset() { 
	const FString HIDDEN_WORD = "planet";

	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return; 
}


