// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuController.h"
#include "NausTFGMultiPlayer/Client/GUI/Menus/MainMenu_EP.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/MainMenuPlayerController.h"
#include "NausTFGMultiPlayer/Client/Controllers/SoundsController.h"

UMainMenuController::UMainMenuController()
{
	numPlayersDataForMainMenuText = 0;
	
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
	mainMenu->SetNumPlayersValue(numPlayersDataForMainMenuText);
	mainMenu->UpdateNumPlayers();
	
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
	soundsController = mainMenuPlayerController->GetWorld()->SpawnActor<ASoundsController>(soundsControllerClass);
}

void UMainMenuController::UnloadMainMenu()
{

	Super::UnloadMenu(mainMenu);
	HideAndLockMouseCursor();
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

	
	mainMenu->signalOnClickImReady.AddDynamic(mainMenuPlayerController, &AMainMenuPlayerController::SetReady);
}

void UMainMenuController::SetRoleToPilot()
{

	mainMenu->SetSelectionRolToPilot();
}

void UMainMenuController::SetRoleToArtillery()
{
	mainMenu->SetSelectionRolToArtillery();
}

void UMainMenuController::SetNumPLayers(int32 numPlayers)
{

	numPlayersDataForMainMenuText = numPlayers;
}

void UMainMenuController::UpdateNumPlayers()
{

	if(mainMenu)
	{
		mainMenu->SetNumPlayersValue(numPlayersDataForMainMenuText);
		mainMenu->UpdateNumPlayers();
	}
	
}


