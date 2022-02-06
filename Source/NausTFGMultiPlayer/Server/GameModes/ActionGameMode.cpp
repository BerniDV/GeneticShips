// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Factories/ReferencePawnsFactory.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/ActionPlayerState.h"

AActionGameMode::AActionGameMode()
{

	DefaultPawnClass = nullptr;
	PlayerStateClass = AActionPlayerState::StaticClass();
	PlayerControllerClass = AActionPlayerController::StaticClass();
	GameStateClass = AActionGameState::StaticClass();
	
}


FString AActionGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueNetId,
	const FString& Options, const FString& Portal)
{

	int teamIdTest = 1;

	MatchOptions matchOptions(Options, teamIdTest);

	AActionPlayerController* playerController = Cast<AActionPlayerController>(NewPlayerController);

	playerController->Initialize(matchOptions);

	return Super::InitNewPlayer(playerController, UniqueNetId, Options, Portal);
	
}


UClass* AActionGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{

	AActionPlayerController* myController = Cast<AActionPlayerController>(InController);

	if (myController)
	{
		UClass* pawn = myController->GetDefaultPawn();

		if(pawn)
		{

			return pawn;

		}
		
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}






