// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "NausTFGMultiPlayer/Client/Controllers/MainMenuController.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Factories/ReferencePawnsFactory.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ArtilleryActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"
#include "Net/UnrealNetwork.h"

AActionPlayerController::AActionPlayerController()
{

	bReplicates = true;
	defaultPawn = nullptr;

	
}

void AActionPlayerController::InitializePresentationController()
{

	if (IsLocalPlayerController())
	{
		//Placeholder para no crash, se sustituye por inGameMenu
		presentationController = NewObject<UMainMenuController>();

		presentationController->Init(this);
	}
}

void AActionPlayerController::BindSignals()
{
	

}

UClass* AActionPlayerController::GetDefaultPawn()
{

	return defaultPawn;
}

void AActionPlayerController::InitializeDefaultPawn(UReferencePawnsFactory* factoryType)
{


	defaultPawn = factoryType->CreateReference();

}

void AActionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionPlayerController, defaultPawn);
}

void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HideAndLockMouseCursor();
}
