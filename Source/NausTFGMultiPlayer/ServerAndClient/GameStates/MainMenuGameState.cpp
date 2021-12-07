// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameState.h"

#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/MainMenuPlayerState.h"
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

int32 AMainMenuGameState::GetNumPlayersReady()
{

	int playersReady = 0;

	for(auto playerState : PlayerArray)
	{

		AMainMenuPlayerState* player = Cast<AMainMenuPlayerState>(playerState);

		if(player->GetIsReady())
		{

			playersReady++;
		}
	}

	return playersReady;
	
	
}

bool AMainMenuGameState::AllPlayersRolesAreDifferent()
{

	bool allDifferents = true;
	bool playersWaiting = false;

	TSet<NausTFGRolTypes> rolTypesUsed;
	TArray<APlayerState*> myPlayerStates = PlayerArray;

	for (auto playerState : myPlayerStates)
	{
		if(!playersWaiting)
			playersWaiting = true;

		AMainMenuPlayerState* player = Cast<AMainMenuPlayerState>(playerState);

		NausTFGRolTypes roleSelected = player->GetRolType();

		if (roleSelected == NausTFGRolTypes::NoneType) {


			return false;
		}

		if(rolTypesUsed.Find(roleSelected))
		{

			allDifferents = false;
			
		}else
		{

			rolTypesUsed.Add(roleSelected);
		}

	}

	return allDifferents && playersWaiting;

}


void AMainMenuGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainMenuGameState, numPlayers);
}

