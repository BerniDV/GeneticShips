// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MainMenuGameState.generated.h"

class AMainMenuPlayerState;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AMainMenuGameState : public AGameState
{
	GENERATED_BODY()

public:

	AMainMenuGameState();

	void SetNumPlayers(int32 num_Players);

	int32 GetNumPlayers();

	int32 GetNumPlayersReady();

	bool AllPlayersRolesAreDifferent();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

private:

	UPROPERTY(Replicated)
	int32 numPlayers;
	
};
