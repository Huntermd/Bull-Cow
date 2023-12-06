// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    // FBullCowCount Count = {2,3};
    
    PrintLine(TEXT("Hello, Input a guess and press enter"));
    Isograms = GetValidWords(Words);
    SetupGame();
   //debugging line.
    
   
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver){
        ClearScreen();
    SetupGame();
    }else{
        ProcessGuess(Input);
    }
    
    
}

void UBullCowCartridge::SetupGame(){
    RandomPos = FMath::RandRange(0,Isograms.Num() - 1);
     HiddenWord = Isograms[RandomPos];
    
     Lives = HiddenWord.Len();
     bGameOver = false;
     
     PrintLine(TEXT("The hidden word is %s"), *HiddenWord);
     PrintLine(TEXT("Guess a %i letter word"), HiddenWord.Len());
     PrintLine(TEXT("You have this many lives %i "), Lives);


       
    
    
}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

void  UBullCowCartridge::ProcessGuess(FString Guess){
    
        if (Guess == HiddenWord){
        PrintLine(TEXT("You won!"));
        //Gameover = true;
        EndGame();
        return;

    }
     if (Guess.Len() != HiddenWord.Len()){
        PrintLine(TEXT("Wrong length"));
        //text
        return;
     }
        if(!IsIsogram(Guess)){
            PrintLine(TEXT("No repeating letters! \n Try again!"));
        }
       --Lives;
            PrintLine(TEXT("you lost a life. \nYou have %i lives left"), Lives);
         if (Lives <= 0){
            ClearScreen();
            PrintLine(TEXT("You are out of lives"));
            // PrintLine(TEXT("The correct answer was: %s"), HiddenWord);
                EndGame();
                return;
             }

        // int32 Bulls,Cows;
        FBullCowCount Score =GetBullCows(Guess) ;
         
         PrintLine(TEXT("You have %i Bulls and %i Cows."), Score.Bulls, Score.Cows);
         PrintLine(Score.BullsText);
         PrintLine(Score.CowsText);
        
                
}

bool UBullCowCartridge::IsIsogram(FString Word) const{
    for(int32 Index = 0; Index < Word.Len(); Index++){
        for(int32 condition = Index + 1; condition< Word.Len(); condition++){
        if(Word[Index] == Word[condition]){
            return false;
        }

    }

    }


    
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const{
     TArray<FString> ValidWords;
     for (FString Word : WordList){
        if (Word.Len() >= 4 && Word.Len() <= 8){
            if(IsIsogram(Word)){
                ValidWords.Emplace(Word);
            }
        }
     }
     
   
     return ValidWords;
}


FBullCowCount UBullCowCartridge::GetBullCows(const FString&Guess)const {
    FBullCowCount Count;

    for(int32 GuessIndex = 0; GuessIndex< Guess.Len(); GuessIndex++){
        if(Guess[GuessIndex]== HiddenWord[GuessIndex]){
            Count.BullsText += Guess[GuessIndex];
            // Count.BullsText += TEXT(", ");
            if(GuessIndex + 1 != Guess.Len()){
                Count.BullsText += TEXT(", ");
            }
            Count.Bulls++;
            continue;
        };
    for(int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++){
        if(Guess[GuessIndex]== HiddenWord[HiddenIndex]){
            Count.CowsText += HiddenWord[HiddenIndex];
            // Count.BullsText += TEXT(", ");
            if(GuessIndex + 1 != Guess.Len()){
                Count.CowsText += TEXT(", ");
            }
            Count.Cows++;
            break;
        };
    };
    };
    return Count;
    //for every index if the guess is the same as that index increase bull count
};



/*
struct FStrutureName{
    type StrtutureM1
}
*/