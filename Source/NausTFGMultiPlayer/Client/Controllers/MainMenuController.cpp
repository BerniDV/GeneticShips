// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuController.h"
#include "NausTFGMultiPlayer/Client/GUI/Menus/MainMenu_EP.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/MainMenuPlayerController.h"

UMainMenuController::UMainMenuController()
{

	InitializeMenus();
}

void UMainMenuController::InitializeMenus()
{

	ConstructorHelpers::FClassFinder <UMainMenu_EP> mainMenuClassBP(TEXT("/Game/Client/GUI/Menus/MainMenu/MainMenu_BP"));
	mainMenuClass = mainMenuClassBP.Class;
}

void UMainMenuController::Init(APlayerController* MovieSceneBlends)
{

	mainMenuPlayerController = Cast<AMainMenuPlayerController>(MovieSceneBlends);
}

void UMainMenuController::CreaMenus()
{
	
	mainMenu = CreateWidget<UMainMenu_EP>(mainMenuPlayerController, mainMenuClass);
}

void UMainMenuController::BindSignals()
{

	BindSetPilotAsRoleSelected();
	BindSetArtilleryAsRoleSelected();
	BindImReadyButton();
}

void UMainMenuController::LoadMainMenu()
{

	Super::LoadMenu(mainMenu);
	ShowNotLockingMouseCursor(mainMenu);
}

void UMainMenuController::UnloadMainMenu()
{

	Super::UnloadMenu(mainMenu);
	HideAndLockMouseCursor(mainMenu);
}

void UMainMenuController::BindSetPilotAsRoleSelected()
{

	mainMenu->signalOnClickPilotButton.AddDynamic(mainMenuPlayerController, &AMainMenuPlayerController::SetRoleToPilot);
}

void UMainMenuController::BindSetArtilleryAsRoleSelected()
{

	mainMenu->signalOnClickArtilleryButton.AddDynamic(mainMenuPlayerController, &AMainMenuPlayerController::SetRoleToArtillery);
}

void UMainMenuController::BindImReadyButton()
{

	mainMenu->signalOnClickImReady.AddDynamic(mainMenuPlayerController, &AMainMenuPlayerController::JoinGame);
}

void UMainMenuController::SetRoleToPilot()
{

	mainMenu->SetSelectionRolToPilot();
}

void UMainMenuController::SetRoleToArtillery()
{
	mainMenu->SetSelectionRolToArtillery();
}


