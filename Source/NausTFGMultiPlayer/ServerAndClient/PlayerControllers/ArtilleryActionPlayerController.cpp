// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtilleryActionPlayerController.h"

#include "ActionPlayerController.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCamera.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ArtilleryActionPawn.h"

AArtilleryActionPlayerController::AArtilleryActionPlayerController()
{

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Artillery Controller Prepared"));

	ConstructorHelpers::FClassFinder <AArtilleryActionPawn> refArtilleryActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/ArtilleryActionPawn_BP"));
	reference = refArtilleryActionPawnBP.Class;
}

void AArtilleryActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Artillery Controller PreparedB"));
}

UClass* AArtilleryActionPlayerController::GetDefaultPawn()
{
	return reference;
}

AActionCamera* AArtilleryActionPlayerController::SpawnActionCamera()
{

	FVector spawnLocation(-440.0f, -340.0f, 230.0f);
	FRotator spawnRotation(7.0f, 4.f, 0.f);

	AActionCamera* camera = GetWorld()->SpawnActor<AActionCamera>(spawnLocation, spawnRotation);

	return camera;
}

void AArtilleryActionPlayerController::PitchCamera(float value)
{
	
}

void AArtilleryActionPlayerController::YawCamera(float value)
{
	

}

void AArtilleryActionPlayerController::Fire()
{

	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->Fire();
}
