// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPlayerController.h"

APilotActionPlayerController::APilotActionPlayerController()
{

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Controller Prepared"));
}

void APilotActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Controller Prepared B"));
}
