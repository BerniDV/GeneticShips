// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyPickUp.h"

#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"

AEnergyPickUp::AEnergyPickUp()
{

	bReplicates = true;
	bAlwaysRelevant = true;
	EnergyAmount = 60.f;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComponent"));
	SetRootComponent(meshComponent);

}

void AEnergyPickUp::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{

		meshComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnergyPickUp::OverlapDetected);
	}

}

void AEnergyPickUp::OverlapDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if(APilotActionPawn* overlapedActor = Cast<APilotActionPawn>(OtherActor))
	{

		overlapedActor->AddEnergy(EnergyAmount);

		signalPickedUp.Broadcast();
	}
}

void AEnergyPickUp::BeginDestroy()
{
	Super::BeginDestroy();


}

void AEnergyPickUp::Tick(float DeltaSeconds)
{
	
}

void AEnergyPickUp::Client_SetActorLocation_Implementation(FVector newLocation)
{

	SetActorLocation(newLocation);
}
