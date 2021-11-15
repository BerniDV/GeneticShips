// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameState.h"

#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/MainMenuPlayerController.h"
#include "Net/UnrealNetwork.h"

AMainMenuGameState::AMainMenuGameState()
{

	bReplicates = true;
}

void AMainMenuGameState::SetNumPlayers(int32 num_Players)
{

	numPlayers = num_Players;
}

int32 AMainMenuGameState::GetNumPlayers()
{
	
	return numPlayers;
}

void AMainMenuGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainMenuGameState, numPlayers);
}

