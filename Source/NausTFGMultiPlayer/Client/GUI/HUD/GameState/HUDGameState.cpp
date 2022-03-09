// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDGameState.h"



void UHUDGameState::SetNumRound(int numRound)
{

	round = numRound;
}

void UHUDGameState::UpdateNumRoundText()
{
	numRoundText = FString::Printf(TEXT("Round: %d"), round);

}

FString UHUDGameState::GetNumRoundText()
{

	return numRoundText;
}

int UHUDGameState::GetNumRound()
{

	return round;
}
