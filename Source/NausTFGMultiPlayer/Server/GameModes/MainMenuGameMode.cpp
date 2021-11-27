// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"

#include "NausTFGMultiPlayer/ServerAndClient/GameStates/MainMenuGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/MainMenuPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/MainMenuPlayerState.h"

AMainMenuGameMode::AMainMenuGameMode()
{

	DefaultPawnClass = nullptr;
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	GameStateClass = AMainMenuGameState::StaticClass();
	PlayerStateClass = AMainMenuPlayerState::StaticClass();

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

	AMainMenuGameState* gameState = GetGameState<AMainMenuGameState>();
	gameState->SetNumPlayers(numPlayers);

	AMainMenuPlayerController* playerController = Cast<AMainMenuPlayerController>(NewPlayer);

	lastPlayerControllerId++;

	playerController->SetId(lastPlayerControllerId);

	PlayerControllerMap.Add(lastPlayerControllerId, playerController);

	UpdateNumPlayers(numPlayers);

	AMainMenuPlayerState* playerState = Cast<AMainMenuPlayerState>(playerController->PlayerState);
	playerState->signalOnPlayerReady.AddDynamic(this, &AMainMenuGameMode::JoinGame);
}

void AMainMenuGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	AMainMenuPlayerController* playerController = Cast<AMainMenuPlayerController>(Exiting);

	int32 idToRemove = playerController->GetId();

	PlayerControllerMap.Remove(idToRemove);

	int32 numPlayers = GetNumPlayers();

	GetGameState<AMainMenuGameState>()->SetNumPlayers(numPlayers);

	UpdateNumPlayers(numPlayers);
}

void AMainMenuGameMode::JoinGame()
{


	if(AreAllPlayersReady())
	{
		if(GetGameState<AMainMenuGameState>()->AllPlayersRolesAreDifferent())
		{

			UWorld* World = GetWorld();

			if (World)
			{

				World->ServerTravel("/Game/Levels/GameLevels/TestGameLevel");
			}
		}

		//Aqui podemos decir que pasa si se repiten roles

	}

}

bool AMainMenuGameMode::AreAllPlayersReady()
{

	AMainMenuGameState* gameState = GetGameState<AMainMenuGameState>();

	int32 playersReady = gameState->GetNumPlayersReady();

	return playersReady == gameState->GetNumPlayers();
}

void AMainMenuGameMode::UpdateNumPlayers(int32 numPlayers)
{

	for(auto& Elem: PlayerControllerMap)
	{

		Elem.Value->UpdateNumPlayers(numPlayers);
	}
}
