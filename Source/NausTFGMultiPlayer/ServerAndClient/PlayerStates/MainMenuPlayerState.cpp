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

	rolSelected = NausTFGRolTypes::NoneType;
	isReady = false;
}

void AMainMenuPlayerState::SetRolType_Implementation(NausTFGRolTypes rolType)
{

	rolSelected = rolType;
	ClientSetRolType(rolType);
}


void AMainMenuPlayerState::ClientSetRolType_Implementation(NausTFGRolTypes rolType)
{

	rolSelected = rolType;
}

NausTFGRolTypes AMainMenuPlayerState::GetRolType()
{

	return rolSelected;
}

void AMainMenuPlayerState::SetIsReady(bool ready)
{
	if(rolSelected != NausTFGRolTypes::NoneType)
	{

		isReady = ready;
		OnPlayerReady();
	}
	
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


