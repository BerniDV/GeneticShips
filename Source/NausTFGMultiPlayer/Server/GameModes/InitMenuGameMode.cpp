// Fill out your copyright notice in the Description page of Project Settings.


#include "InitMenuGameMode.h"

#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/InitMenuPlayerController.h"

AInitMenuGameMode::AInitMenuGameMode()
{

	DefaultPawnClass = nullptr;
	PlayerControllerClass = AInitMenuPlayerController::StaticClass();

}
