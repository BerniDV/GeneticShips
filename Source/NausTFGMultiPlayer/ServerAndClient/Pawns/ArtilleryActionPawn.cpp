// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtilleryActionPawn.h"

#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Projectiles/BasicProjectile.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/RotationComponent.h"
#include "Net/UnrealNetwork.h"

AArtilleryActionPawn::AArtilleryActionPawn()
{

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	//bNetUseOwnerRelevancy = true;
	//NetCullDistanceSquared = 1000000.f;
	bOnlyRelevantToOwner = false;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Artillery Pawn Prepared"));


	ConstructorHelpers::FClassFinder <ABasicProjectile> refBasicProjectileBP(TEXT("/Game/ServerAndClient/Projectiles/BasicProjectile_BP"));
	projectile = refBasicProjectileBP.Class;

	rotationComponent = CreateDefaultSubobject<URotationComponent>(TEXT("rotationComponent"));
	rotationComponent->SetIsReplicated(true);
	
}

void AArtilleryActionPawn::Fire()
{

	Server_Fire(GetActorLocation());

}

void AArtilleryActionPawn::StopFire()
{

	
}

bool AArtilleryActionPawn::IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget,
	const FVector& SrcLocation) const
{
	
	return Super::IsNetRelevantFor(RealViewer, ViewTarget, SrcLocation);
}

void AArtilleryActionPawn::ExecuteRotation(FRotator rotator)
{

	rotationComponent->ExecuteRotation(rotator);
}

void AArtilleryActionPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AArtilleryActionPawn, rotationComponent);
	DOREPLIFETIME_CONDITION(AArtilleryActionPawn, position, COND_SkipOwner);
	
}

void AArtilleryActionPawn::PlayDeath_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Black, "Death");
}


void AArtilleryActionPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(HasAuthority())
	{

		position = GetActorLocation();
	}else if(GetLocalRole() == ROLE_SimulatedProxy)
	{

		SetActorLocation(position);
	}
	
}

void AArtilleryActionPawn::Server_Fire_Implementation(FVector locationToFire)
{

	const FVector spawnLocation = locationToFire + GetActorRotation().Vector() * 100.f;
	const FRotator spawnRotation = GetActorRotation();

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;

	ABasicProjectile* BasicProjectile =  GetWorld()->SpawnActor<ABasicProjectile>(projectile, spawnLocation, spawnRotation, spawnParameters);

}

bool AArtilleryActionPawn::Server_Fire_Validate(FVector locationToFire)
{

	AActionPlayerController* PC = Cast<AActionPlayerController>(GetOwner());

	return PC->GetTimeSinceLastProjectile() >= PC->GetCadency();

}

