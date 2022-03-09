// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateHUD_EP.h"


UGameStateHUD_EP::UGameStateHUD_EP()
{

	round = 0;
	numRoundText = "Round: 0";
}

void UGameStateHUD_EP::SetNumRound(int numRound)
{

	round = numRound;
}

void UGameStateHUD_EP::UpdateNumRoundText()
{
	

	numRoundText = FString::Printf(TEXT("Round: %d"), round);
}

FString UGameStateHUD_EP::GetNumRoundText()
{

	return numRoundText;
}

int UGameStateHUD_EP::GetNumRound()
{

	return round;
}
