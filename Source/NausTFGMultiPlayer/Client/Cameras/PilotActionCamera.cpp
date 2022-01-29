// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionCamera.h"

APilotActionCamera::APilotActionCamera()
{

	PrimaryActorTick.bCanEverTick = true;
}

void APilotActionCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

void APilotActionCamera::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
