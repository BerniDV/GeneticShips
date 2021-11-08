// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"

#include "NausTFGMultiPlayer/Client/Levels/Cameras/MainMenuCameraActor.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{


}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FVector spawnLocation(-440.0f, -340.0f, 230.0f);
	FRotator spawnRotation(7.0f, 4.f, 0.f);

	cameraActor = GetWorld()->SpawnActor<AMainMenuCameraActor>(spawnLocation, spawnRotation);

	SetViewTarget(cameraActor);
}
