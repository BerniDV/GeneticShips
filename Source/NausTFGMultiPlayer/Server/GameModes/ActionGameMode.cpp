// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionGameMode.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"

AActionGameMode::AActionGameMode()
{

	DefaultPawnClass = nullptr;
	PlayerControllerClass = AActionPlayerController::StaticClass();


}
