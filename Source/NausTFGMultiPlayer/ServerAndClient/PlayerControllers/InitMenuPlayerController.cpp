// Fill out your copyright notice in the Description page of Project Settings.


#include "InitMenuPlayerController.h"

#include "NausTFGMultiPlayer/Client/Controllers/InitMenuController.h"

AInitMenuPlayerController::AInitMenuPlayerController()
{
	
	InitializePresentationController();
}

void AInitMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();


	LoadInitMenu();
	
}

void AInitMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::AnyKey, EInputEvent::IE_Pressed, this, &AInitMenuPlayerController::AnyKeyPressed);
}

void AInitMenuPlayerController::InitializePresentationController()
{

	if(IsLocalPlayerController())
	{

		presentationController = NewObject<UInitMenuController>();
		
		presentationController->Init(this);
	}
	
}


void AInitMenuPlayerController::AnyKeyPressed()
{
	if(IsLocalPlayerController())
	{

		Cast<UInitMenuController>(presentationController)->AnyKeyPressed();
	}
	
}

void AInitMenuPlayerController::JoinServerRoom()
{

	if(IsLocalPlayerController())
	{


		FString URL("25.55.225.211");

		ClientTravel(URL, ETravelType::TRAVEL_Absolute);

	}
	

}

void AInitMenuPlayerController::BindSignals()
{
	Super::BindSignals();

	if(IsLocalPlayerController())
	{

		Cast<UInitMenuController>(presentationController)->BindAnyKeySignal();

	}
}

void AInitMenuPlayerController::LoadInitMenu()
{

	if(IsLocalPlayerController())
	{

		Cast<UInitMenuController>(presentationController)->LoadInitMenu();

	}
}

void AInitMenuPlayerController::UnloadInitMenu()
{

	if(IsLocalPlayerController())
	{

		Cast<UInitMenuController>(presentationController)->UnloadInitMenu();

	}
	
}




