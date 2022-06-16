// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStateHUD_EP.h"


UGameStateHUD_EP::UGameStateHUD_EP()
{

	round = 0;
	roundCountDownInSeconds = 0.f;
	roundCountDownText = "0:0:0";
	numRoundText = "Round: 0";

	enemiesAlive = 0;
	enemiesAliveText = "Enemies: 0";
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

FString UGameStateHUD_EP::GetRoundCountDownText()
{

	return roundCountDownText;
}

int UGameStateHUD_EP::GetNumRound()
{

	return round;
}

int UGameStateHUD_EP::GetRoundCountDownInSeconds()
{

	return roundCountDownInSeconds;
}

void UGameStateHUD_EP::SetRoundCountDownInSeconds(int _roundCountDownInSeconds)
{

	roundCountDownInSeconds = _roundCountDownInSeconds;
}

void UGameStateHUD_EP::SetEnemiesAlive(int enemies)
{

	enemiesAlive = enemies;
}

void UGameStateHUD_EP::UpdateEnemiesAliveText()
{

	enemiesAliveText = FString::Printf(TEXT("Enemies: %d"), enemiesAlive);
}

void UGameStateHUD_EP::UpdateRoundCountDownText()
{

	//passar de segundos -> h:m:s
	int hours = roundCountDownInSeconds / 3600;
	int min = (roundCountDownInSeconds % 3600) / 60;
	int sec = roundCountDownInSeconds % 60;

	roundCountDownText = FString::Printf(TEXT("%d:%d:%d"), hours, min, sec);
}

FString UGameStateHUD_EP::GetEnemiesAliveText()
{

	return enemiesAliveText;
}

int UGameStateHUD_EP::GetEnemiesAlive()
{

	return enemiesAlive;
}
