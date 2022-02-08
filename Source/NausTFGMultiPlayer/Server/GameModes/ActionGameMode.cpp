// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Factories/ReferencePawnsFactory.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerControllerImpl.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/ActionPlayerState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"

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


void AActionGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AActionPlayerController* PC = Cast<AActionPlayerController>(NewPlayer);

	int teamId = PC->GetTeamId();
	
	for (auto x : GameState->PlayerArray)
	{
		//Si no somos nosotras mismos y somos del mismo equipo nos asignamos como compañero
		if (x->GetPlayerId() != NewPlayer->GetPlayerState<AActionPlayerState>()->GetPlayerId() && Cast<AActionPlayerState>(x)->GetTeamID() == teamId)
		{

			AActionPawn* teamMate = Cast<AActionPawn>(x->GetPawn());

			//nos lo asignamos como compañero
			PC->GetPlayerControllerImpl()->SetTeamMate(teamMate);

			AActionPlayerController* PCTeamMate = Cast<AActionPlayerController>(teamMate->GetOwner());

			//Nos asignamos como compañero
			AActionPawn* myPawn = Cast<AActionPawn>(NewPlayer->GetPawn());
			PCTeamMate->GetPlayerControllerImpl()->SetTeamMate(myPawn);
		}
	}
}






