// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

#include "NausTFGMultiPlayer/Client/Controllers/MainMenuController.h"
#include "NausTFGMultiPlayer/Client/Levels/Cameras/MainMenuCameraActor.h"
#include "NausTFGMultiPlayer/Server/GameModes/MainMenuGameMode.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/MainMenuGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Singletons/CustomGameInstance.h"
#include "Engine/World.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/MainMenuPlayerState.h"


AMainMenuPlayerController::AMainMenuPlayerController()
{


	InitializePresentationController();
	

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
	FRotator spawnRotation(7.0f, 94.f, 0.f);

	AMainMenuCameraActor* camera = GetWorld()->SpawnActor<AMainMenuCameraActor>(spawnLocation, spawnRotation);

	SetCameraActor(camera);

	SetViewTarget(camera);
}

void AMainMenuPlayerController::SetRoleToPilot()
{
	NausTFGRolTypes rol = NausTFGRolTypes::PilotActionRolType;
	Cast<UMainMenuController>(presentationController)->SetRoleToPilot();
	GetPlayerState<AMainMenuPlayerState>()->SetRolType(rol);
	
}

void AMainMenuPlayerController::SetRoleToArtillery()
{

	NausTFGRolTypes rol = NausTFGRolTypes::ArtilleryActionRolType;
	Cast<UMainMenuController>(presentationController)->SetRoleToArtillery();
	GetPlayerState<AMainMenuPlayerState>()->SetRolType(rol);
	
}

void AMainMenuPlayerController::SetReady_Implementation(bool ready)
{

	NausTFGRolTypes rol = GetPlayerState<AMainMenuPlayerState>()->GetRolType();

	if(!IsLocalPlayerController() && rol != NausTFGRolTypes::NoneType)
	{

		GetPlayerState<AMainMenuPlayerState>()->SetIsReady(ready);

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

void AMainMenuPlayerController::ClientTravelInternal_Implementation(const FString& URL, ETravelType Travel,
	bool bSeamless, FGuid MapPackageGuid)
{

	NausTFGRolTypes rol = GetPlayerState<AMainMenuPlayerState>()->GetRolType();

	FString URLWithParameters = URL + FString::Printf(TEXT("?Role=%d"), rol);

	Super::ClientTravelInternal_Implementation(URLWithParameters, Travel, bSeamless, MapPackageGuid);

}


void AMainMenuPlayerController::SetId(int32 ID)
{

	Id = ID;
}

int32 AMainMenuPlayerController::GetId()
{

	return Id;
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreaMenus();
	BindSignals();
	
	LoadMainMenu();

	SpawnMainMenuCamera();

	if(!HasAuthority())
		presentationController->SpawnSoundAtLocation(FVector::ZeroVector, Sounds::MainMenuMusic, 0.3);
}
