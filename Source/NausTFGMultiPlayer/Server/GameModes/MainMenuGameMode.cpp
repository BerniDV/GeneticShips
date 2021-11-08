// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/MainMenuPlayerController.h"

AMainMenuGameMode::AMainMenuGameMode()
{

	DefaultPawnClass = nullptr;
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}
