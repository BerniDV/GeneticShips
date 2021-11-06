// Fill out your copyright notice in the Description page of Project Settings.


#include "InitMenuPlayerController.h"

#include "NausTFGMultiPlayer/Client/GUI/Menus/InitMenu_EP.h"

AInitMenuPlayerController::AInitMenuPlayerController()
{

	InitializeMenus();

}

void AInitMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreaMenus();

	bindSignals();

	LoadMenu(initMenu);
	
}

void AInitMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::AnyKey, EInputEvent::IE_Pressed, this, &AInitMenuPlayerController::AnyKeyPressed);
}

void AInitMenuPlayerController::InitializeMenus()
{

	if(IsLocalPlayerController())
	{

		ConstructorHelpers::FClassFinder <UInitMenu_EP> initMenuClassBP(TEXT("/Game/Client/GUI/Menus/InitMenu/InitMenu_BP"));
		initMenuClass = initMenuClassBP.Class;
	}
	
}

void AInitMenuPlayerController::CreaMenus()
{

	if (IsLocalPlayerController())
	{
		initMenu = CreateWidget<UInitMenu_EP>(this, initMenuClass);

	}
}

void AInitMenuPlayerController::AnyKeyPressed()
{
	if(IsLocalPlayerController())
	{

		initMenu->OnClickAnyKey();
	}
	
}

void AInitMenuPlayerController::JoinServerRoom()
{

	if(IsLocalPlayerController())
	{


		FString URL("127.0.0.1");

		ClientTravel(URL, ETravelType::TRAVEL_Absolute);

	}
	

}

void AInitMenuPlayerController::bindSignals()
{
	Super::bindSignals();

	if(IsLocalPlayerController())
	{

		initMenu->signalOnClickAnyKey.AddDynamic(this, &AInitMenuPlayerController::JoinServerRoom);

	}
}




