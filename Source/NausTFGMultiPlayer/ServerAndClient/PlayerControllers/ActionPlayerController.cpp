// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "NausTFGMultiPlayer/Client/Controllers/MainMenuController.h"

AActionPlayerController::AActionPlayerController()
{


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
