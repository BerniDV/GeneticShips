// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameState.h"

#include "GameFramework/PlayerState.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "Net/UnrealNetwork.h"

AActionGameState::AActionGameState()
{

	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	round = 0;
}

void AActionGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionGameState, round);
	DOREPLIFETIME(AActionGameState, enemiesAlive);
}

void AActionGameState::PlayerDead()
{

	signalPlayerDead.Broadcast();
}

void AActionGameState::SetRound(int newRound)
{
	round = newRound;
	ClientUpdateRound();

}

void AActionGameState::ClientUpdateRound_Implementation()
{

	signalNewRound.Broadcast();
}


void AActionGameState::ClientUpdateEnemies_Implementation()
{

	signalEnemiesAlive.Broadcast();
}

int AActionGameState::GetRound()
{

	return round;
}

int AActionGameState::GetEnemiesAlive()
{

	return enemiesAlive;
}

void AActionGameState::SetEnemiesAlive(int numEnemies)
{

	enemiesAlive = numEnemies;
	ClientUpdateEnemies();
}


