// Fill out your copyright notice in the Description page of Project Settings.


#include "InitMenuController.h"
#include "NausTFGMultiPlayer/Client/GUI/Menus/InitMenu_EP.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/InitMenuPlayerController.h"


UInitMenuController::UInitMenuController()
{

	InitializeMenus();
}

void UInitMenuController::InitializeMenus()
{

	ConstructorHelpers::FClassFinder <UInitMenu_EP> initMenuClassBP(TEXT("/Game/Client/GUI/Menus/InitMenu/InitMenu_BP"));
	initMenuClass = initMenuClassBP.Class;
	
}

void UInitMenuController::Init(APlayerController* owner)
{
	
	initMenuPlayerController = Cast<AInitMenuPlayerController>(owner);
}


void UInitMenuController::CreaMenus()
{

	initMenu = CreateWidget<UInitMenu_EP>(initMenuPlayerController, initMenuClass);
}


void UInitMenuController::LoadInitMenu()
{

	Super::LoadMenu(initMenu);
	
}

void UInitMenuController::UnloadInitMenu()
{

	Super::UnloadMenu(initMenu);

}

void UInitMenuController::AnyKeyPressed()
{

	initMenu->OnClickAnyKey();
}

void UInitMenuController::BindAnyKeySignal()
{

	initMenu->signalOnClickAnyKey.AddDynamic(initMenuPlayerController, &AInitMenuPlayerController::JoinServerRoom);
}
