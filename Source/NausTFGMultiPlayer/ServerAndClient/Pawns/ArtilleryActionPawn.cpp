// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtilleryActionPawn.h"

#include "NausTFGMultiPlayer/ServerAndClient/Projectiles/BasicProjectile.h"

AArtilleryActionPawn::AArtilleryActionPawn()
{

	bReplicates = true;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Artillery Pawn Prepared"));


	ConstructorHelpers::FClassFinder <ABasicProjectile> refBasicProjectileBP(TEXT("/Game/ServerAndClient/Projectiles/BasicProjectile_BP"));
	projectile = refBasicProjectileBP.Class;
	
}

void AArtilleryActionPawn::Fire()
{

	Server_Fire();

}

void AArtilleryActionPawn::Server_Fire_Implementation()
{

	const FVector spawnLocation = GetActorLocation() + (GetActorRotation().Vector() * 100.0f) + (GetActorUpVector() * 50.0f);
	const FRotator spawnRotation = GetActorRotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;

	ABasicProjectile* BasicProjectile =  GetWorld()->SpawnActor<ABasicProjectile>(projectile, spawnLocation, spawnRotation, spawnParameters);
}

bool AArtilleryActionPawn::Server_Fire_Validate()
{

	return true;

}

