// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtilleryActionPlayerController.h"

#include "ActionPlayerController.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCamera.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ArtilleryActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"

AArtilleryActionPlayerController::AArtilleryActionPlayerController()
{

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Artillery Controller Prepared"));

	ConstructorHelpers::FClassFinder <AArtilleryActionPawn> refArtilleryActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/ArtilleryActionPawn_BP"));
	reference = refArtilleryActionPawnBP.Class;

	cadencyOfTheGunInSeconds = 0.1f;
	bIsShooting = false;
	timeSinceLastProjectile = 0.f;
}

void AArtilleryActionPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Artillery Controller PreparedB"));
}

void AArtilleryActionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	timeSinceLastProjectile += DeltaSeconds;

	if(bIsShooting && timeSinceLastProjectile >= cadencyOfTheGunInSeconds)
	{

		timeSinceLastProjectile = 0.f;
		Fire();
	}
}

UClass* AArtilleryActionPlayerController::GetDefaultPawn()
{
	return reference;
}

AActionCamera* AArtilleryActionPlayerController::SpawnActionCamera()
{

	AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner());
	AArtilleryActionPawn* pawn = Cast<AArtilleryActionPawn>(PC->GetPawn());

	FVector spawnLocation = pawn->GetActorLocation();
	FRotator spawnRotation = pawn->GetActorRotation();

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

void AArtilleryActionPlayerController::StopShooting()
{

	bIsShooting = false;
	AActionPlayerController* playerController = Cast<AActionPlayerController>(GetOwner());
	Cast<AActionPawn>(playerController->GetPawn())->StopFire();
}

float AArtilleryActionPlayerController::GetCadency()
{

	return cadencyOfTheGunInSeconds;
}

float AArtilleryActionPlayerController::GetTimeSinceLastProjectile()
{

	return timeSinceLastProjectile;
}

void AArtilleryActionPlayerController::StartShooting()
{

	bIsShooting = true;
}
