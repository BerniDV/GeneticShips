// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameController.h"
#include "NausTFGMultiPlayer/Client/GUI/HUD/ArtilleryHUD_EP.h"
#include "NausTFGMultiPlayer/Client/Controllers/VisualEffectsController.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"

UActionGameController::UActionGameController()
{

	InitializeMenus();
}

void UActionGameController::InitializeMenus()
{

	ConstructorHelpers::FClassFinder <UArtilleryHUD_EP> artilleryHUDClassBP(TEXT("/Game/Client/GUI/HUD/ArtilleryHUD_BP"));
	HUDClass = artilleryHUDClassBP.Class;
}

void UActionGameController::Init(APlayerController* owner)
{
	actionPlayerController = Cast<AActionPlayerController>(owner);
}

void UActionGameController::CreaMenus()
{

	artilleryHUD = CreateWidget<UArtilleryHUD_EP>(actionPlayerController, HUDClass);

	//Crea el controlador de efectos visuales, es actor ya que en objeto unreal anulaba las referencias de punteros por algun motivo
	visualEffectsController = GetWorld()->SpawnActor<AVisualEffectsController>();

}

void UActionGameController::BindSignals()
{
	
}

void UActionGameController::LoadHUD()
{

	Super::LoadMenu(artilleryHUD);
}

void UActionGameController::UnloadHUD()
{

	Super::UnloadMenu(artilleryHUD);
}

void UActionGameController::SpawnParticlesAtLocation(FVector Location, FVector Scale)
{
	
	Super::SpawnParticlesAtLocation(Location, Scale);

}




