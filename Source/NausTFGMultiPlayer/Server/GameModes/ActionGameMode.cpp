// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Factories/ReferencePawnsFactory.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ArtilleryActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/PilotActionPlayerController.h"
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

	NausTFGRolTypes_Enum roleSelected = (NausTFGRolTypes_Enum) FCString::Atoi(*UGameplayStatics::ParseOption(Options, TEXT("Role")));

	AActionPlayerController* playerController = Cast<AActionPlayerController>(NewPlayerController);

	UReferencePawnsFactory* factory = UReferencePawnsFactory::GetInstance();

	playerController->InitializeDefaultPawn(factory->GetFactory(roleSelected));

	return Super::InitNewPlayer(playerController, UniqueNetId, Options, Portal);
}

void AActionGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

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
