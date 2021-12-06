// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionMainMenuController.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"

UActionMainMenuController::UActionMainMenuController()
{
}

void UActionMainMenuController::InitializeMenus()
{
	//ConstructorHelpers::FClassFinder <UActionMainMenu_EP> actionMainMenuClassBP(TEXT("/Game/Client/GUI/Menus/MainMenu/ActionMainMenu_BP"));
	//actionMainMenuClass = actionMainMenuClassBP.Class;
}

void UActionMainMenuController::Init(APlayerController* Owner)
{
	actionPlayerController = Cast<AActionPlayerController>(Owner);
}

void UActionMainMenuController::CreaMenus()
{
	//actionMainMenu = CreateWidget<UActionMainMenu_EP>(actionPlayerController, actionMainMenuClass);
}

void UActionMainMenuController::BindSignals()
{
	//Signals
}
