// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerState.h"

#include "NausTFGMultiPlayer/Server/GameModes/MainMenuGameMode.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/MainMenuGameState.h"
#include "Net/UnrealNetwork.h"

void AMainMenuPlayerState::OnPlayerReady()
{

	signalOnPlayerReady.Broadcast();
}

AMainMenuPlayerState::AMainMenuPlayerState()
{

	rolSelected = NausTFGRolTypes_Enum::NoneType;
	isReady = false;
}

void AMainMenuPlayerState::SetRolType_Implementation(NausTFGRolTypes_Enum rolType)
{

	rolSelected = rolType;
	
}


NausTFGRolTypes_Enum AMainMenuPlayerState::GetRolType()
{

	return rolSelected;
}

void AMainMenuPlayerState::SetIsReady(bool ready)
{

	isReady = ready;
	OnPlayerReady();
}

bool AMainMenuPlayerState::GetIsReady()
{
	return isReady;
}

void AMainMenuPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainMenuPlayerState, rolSelected);

}


