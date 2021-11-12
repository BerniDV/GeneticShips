// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

#include "NausTFGMultiPlayer/Client/Controllers/MainMenuController.h"
#include "NausTFGMultiPlayer/Client/Levels/Cameras/MainMenuCameraActor.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"

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

		Cast<UMainMenuController>(presentationController)->BindSetPilotAsRoleSelected();

		Cast<UMainMenuController>(presentationController)->BindSetArtilleryAsRoleSelected();
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
}

void AMainMenuPlayerController::SetRoleToArtillery()
{

	roleSelected = NausTFGRolTypes_Enum::ArtilleryActionRolType;
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	LoadMainMenu();

	SpawnMainMenuCamera();
}
