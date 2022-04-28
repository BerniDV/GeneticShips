// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionGameController.h"

#include "NausTFGMultiPlayer/Client/GUI/HUD/PilotHUD_EP.h"

UPilotActionGameController::UPilotActionGameController()
{

	InitializeMenus();
}

void UPilotActionGameController::CreaMenus()
{
	Super::CreaMenus();

	pilotHUD = CreateWidget<UPilotHUD_EP>(actionPlayerController, PawnHUDClass);
}

void UPilotActionGameController::LoadHUD()
{
	Super::LoadHUD();
	
	Super::LoadMenu(pilotHUD);

}

void UPilotActionGameController::UnloadHUD()
{
	Super::UnloadHUD();

	Super::UnloadMenu(pilotHUD);
}

void UPilotActionGameController::InitializeMenus()
{
	Super::InitializeMenus();

	ConstructorHelpers::FClassFinder <UPilotHUD_EP> pilotHUDClassBP(TEXT("/Game/Client/GUI/HUD/PilotHUD_BP"));
	PawnHUDClass = pilotHUDClassBP.Class;

}

void UPilotActionGameController::UpdateHealth(float health)
{

	pilotHUD->SetLifeRendered(health);
}

void UPilotActionGameController::UpdateEnergy(float energy)
{

	pilotHUD->SetEnergyRendered(energy);
}
