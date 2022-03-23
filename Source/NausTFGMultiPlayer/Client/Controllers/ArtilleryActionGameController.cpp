// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtilleryActionGameController.h"

#include "Blueprint/UserWidget.h"
#include "NausTFGMultiPlayer/Client/GUI/HUD/ArtilleryHUD_EP.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"


UArtilleryActionGameController::UArtilleryActionGameController()
{

	InitializeMenus();

}

void UArtilleryActionGameController::InitializeMenus()
{
	Super::InitializeMenus();

	ConstructorHelpers::FClassFinder <UArtilleryHUD_EP> artilleryHUDClassBP(TEXT("/Game/Client/GUI/HUD/ArtilleryHUD_BP"));
	PawnHUDClass = artilleryHUDClassBP.Class;
}

void UArtilleryActionGameController::CreaMenus()
{
	Super::CreaMenus();

	artilleryHUD = CreateWidget<UArtilleryHUD_EP>(actionPlayerController, PawnHUDClass);
}

void UArtilleryActionGameController::LoadHUD()
{
	Super::LoadHUD();

	Super::LoadMenu(artilleryHUD);
}

void UArtilleryActionGameController::UnloadHUD()
{
	Super::UnloadHUD();

	Super::UnloadMenu(artilleryHUD);
}
