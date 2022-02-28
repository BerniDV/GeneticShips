// Fill out your copyright notice in the Description page of Project Settings.


#include "Chromosome.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AChromosome::AChromosome()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
}

void AChromosome::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChromosome, sizeGene);
}

void AChromosome::Destroyed()
{
	Super::Destroyed();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Chromosome Destroyed"));
}

FVector AChromosome::GetSizeGene()
{

	return sizeGene;
}

void AChromosome::SetSizeGene(FVector SizeGene)
{

	sizeGene = SizeGene;
	
}

void AChromosome::SetRandomGenes()
{
	sizeGene = FVector(FMath::RandRange(1, 4));
}

void AChromosome::ApplyFenotipe()
{

	AActor* myOwner = GetOwner();

	if(myOwner)
		myOwner->SetActorScale3D(sizeGene);
}

// Called when the game starts or when spawned
void AChromosome::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AChromosome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

