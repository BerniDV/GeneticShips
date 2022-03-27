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

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	timeAlive = 0.f;
	damageCausedToTarget = 0.f;
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
	sizeGene = FVector(FMath::RandRange(1, 1));
}

void AChromosome::Mutation()
{

	sizeGene = FVector(FMath::RandRange(1, 10));
}

AChromosome* AChromosome::Clone()
{

	AChromosome* clonedChromosome = GetWorld()->SpawnActor<AChromosome>();

	clonedChromosome->SetSizeGene(sizeGene);
	clonedChromosome->SetDamageCausedTopTarget(damageCausedToTarget);
	clonedChromosome->SetTimeAlive(timeAlive);

	return clonedChromosome;
}

void AChromosome::SetDamageCausedTopTarget(float amount)
{

	damageCausedToTarget = amount;
}

float AChromosome::GetDamageCausedToTarget()
{

	return damageCausedToTarget;
}

void AChromosome::AddDamageCausedToTarget(float amount)
{

	damageCausedToTarget += amount;
}

float AChromosome::GetTimeAlive()
{

	return timeAlive;
}

void AChromosome::SetTimeAlive(float time)
{

	timeAlive = time;
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

	timeAlive += DeltaTime;

}

