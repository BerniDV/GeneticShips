// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPlayerController.h"

#include "ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/RotationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"

APilotActionPlayerController::APilotActionPlayerController()
{

	bReplicates = true;
	//bAlwaysRelevant = true;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Controller Prepared"));

	ConstructorHelpers::FClassFinder <APilotActionPawn> refPilotActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/PilotActionPawn_BP"));
	reference = refPilotActionPawnBP.Class;

	rotationComponent = CreateDefaultSubobject<URotationComponent>(TEXT("rotationComponent"));

}

void APilotActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Controller Prepared"));

}

void APilotActionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	
}

UClass* APilotActionPlayerController::GetDefaultPawn()
{

	return reference;
}

void APilotActionPlayerController::Rotate(float turnValue)
{

	rotationComponent->ExecuteRotation(turnValue);
	
}
