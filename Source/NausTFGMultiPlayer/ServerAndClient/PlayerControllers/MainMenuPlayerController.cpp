// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

#include "NausTFGMultiPlayer/Client/Controllers/MainMenuController.h"
#include "NausTFGMultiPlayer/Client/Levels/Cameras/MainMenuCameraActor.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/MainMenuGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Singletons/CustomGameInstance.h"


AMainMenuPlayerController::AMainMenuPlayerController()
{


	InitializePresentationController();
	
	roleSelected = NausTFGRolTypes_Enum::NoneType;

}

void AMainMenuPlayerController::InitializePresentationController()
{
	
	if (IsLocalPlayerController())
	{

		presentationController = NewObject<UMainMenuController>();

		presentationController->Init(this);
	}

}


void AMainMenuPlayerController::BindSignals()
{
	Super::BindSignals();

	if(IsLocalPlayerController())
	{

		Cast<UMainMenuController>(presentationController)->BindSignals();
	}
}

void AMainMenuPlayerController::LoadMainMenu()
{

	if (IsLocalPlayerController())
	{

		Cast<UMainMenuController>(presentationController)->LoadMainMenu();

	}
}

void AMainMenuPlayerController::UnloadMainMenu()
{

	if (IsLocalPlayerController())
	{

		Cast<UMainMenuController>(presentationController)->LoadMainMenu();

	}
}

void AMainMenuPlayerController::SpawnMainMenuCamera()
{

	FVector spawnLocation(-440.0f, -340.0f, 230.0f);
	FRotator spawnRotation(7.0f, 4.f, 0.f);

	AMainMenuCameraActor* camera = GetWorld()->SpawnActor<AMainMenuCameraActor>(spawnLocation, spawnRotation);

	SetCameraActor(camera);

	SetViewTarget(camera);
}

void AMainMenuPlayerController::SetRoleToPilot()
{
	roleSelected = NausTFGRolTypes_Enum::PilotActionRolType;
	Cast<UMainMenuController>(presentationController)->SetRoleToPilot();
	Cast<UCustomGameInstance>(GetGameInstance())->SetRoleSelected(roleSelected);
}

void AMainMenuPlayerController::SetRoleToArtillery()
{

	roleSelected = NausTFGRolTypes_Enum::ArtilleryActionRolType;
	Cast<UMainMenuController>(presentationController)->SetRoleToArtillery();
	Cast<UCustomGameInstance>(GetGameInstance())->SetRoleSelected(roleSelected);
}

void AMainMenuPlayerController::JoinGame_Implementation()
{
	if(!IsLocalPlayerController())
	{

		UWorld* World = GetWorld();

		if (World)
		{

			World->ServerTravel("/Game/Levels/GameLevels/TestGameLevel");
		}

	}
	
}


void AMainMenuPlayerController::UpdateNumPlayers_Implementation(int32 numPlayers)
{
	if (IsLocalPlayerController())
	{

		Cast<UMainMenuController>(presentationController)->SetNumPLayers(numPlayers);
		Cast<UMainMenuController>(presentationController)->UpdateNumPlayers();

	}
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	LoadMainMenu();

	SpawnMainMenuCamera();

}
