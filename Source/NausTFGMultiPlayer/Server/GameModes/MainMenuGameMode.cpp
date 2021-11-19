// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "NausTFGMultiPlayer/ServerAndClient/GameStates/MainMenuGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/MainMenuPlayerController.h"

AMainMenuGameMode::AMainMenuGameMode()
{

	DefaultPawnClass = nullptr;
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	GameStateClass = AMainMenuGameState::StaticClass();

	lastPlayerControllerId = 0;
	
}

void AMainMenuGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueNetId,
	FString& ErrorMessage)
{
	
	Super::PreLogin(Options, Address, UniqueNetId, ErrorMessage);

	if(GetNumPlayers() >= 2)
	{
		ErrorMessage = TEXT("Lobby is full");
		FGameModeEvents::GameModePreLoginEvent.Broadcast(this, UniqueNetId, ErrorMessage);
		
	}

	
}

void AMainMenuGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	int32 numPlayers = GetNumPlayers();

	GetGameState<AMainMenuGameState>()->SetNumPlayers(numPlayers);

	AMainMenuPlayerController* playerController = Cast<AMainMenuPlayerController>(NewPlayer);

	lastPlayerControllerId++;

	playerController->SetId(lastPlayerControllerId);

	PlayerControllerMap.Add(lastPlayerControllerId, playerController);

	UpdateNumPlayers(numPlayers);
}

void AMainMenuGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AMainMenuPlayerController* playerController = Cast<AMainMenuPlayerController>(Exiting);

	int32 idToRemove = playerController->GetId();

	PlayerControllerMap.Remove(idToRemove);

	int32 numPlayers = GetNumPlayers();

	UpdateNumPlayers(numPlayers);
}

void AMainMenuGameMode::UpdateNumPlayers(int32 numPlayers)
{

	for(auto& Elem: PlayerControllerMap)
	{

		Elem.Value->UpdateNumPlayers(numPlayers);
	}
}
