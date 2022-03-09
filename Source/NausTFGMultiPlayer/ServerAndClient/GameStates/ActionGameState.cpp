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
}

void AActionGameState::PlayerDead()
{

	signalPlayerDead.Broadcast();
}

void AActionGameState::SetRound(int newRound)
{
	round = newRound;
	signalNewRound.Broadcast();

}

void AActionGameState::ClientUpdateRound_Implementation()
{

	signalNewRound.Broadcast();
}


int AActionGameState::GetRound()
{

	return round;
}


