// Fill out your copyright notice in the Description page of Project Settings.


#include "Chromosome.h"

#include "ParameterCollection.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AChromosome::AChromosome()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bNetUseOwnerRelevancy = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	bAlive = true;

}

void AChromosome::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AChromosome, genesArray);

}

void AChromosome::Destroyed()
{
	Super::Destroyed();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Chromosome Destroyed"));
}

FVector AChromosome::GetSizeGene()
{

	return FVector(genesArray[0]);
}

void AChromosome::SetSizeGene(FVector SizeGene)
{

	genesArray[0] = SizeGene.X;
	
}

void AChromosome::SetRandomGenes()
{
	genesArray[0] = FMath::RandRange(1, 1);
	genesArray[3] = FMath::FRandRange(0.f, 25.f);

	genesArray[4] = FMath::FRandRange(0.f, 100.f);
	genesArray[5] = FMath::FRandRange(0.f, 100.f);
	genesArray[6] = FMath::FRandRange(0.f, 100.f);
	genesArray[7] = FMath::FRandRange(0.f, 100.f);
	genesArray[8] = FMath::FRandRange(0.f, 100.f);
	genesArray[9] = FMath::FRandRange(0.f, 50.f);
	genesArray[10] = FMath::FRandRange(0.f, 100.f);
	genesArray[11] = FMath::FRandRange(0.f, 10.f);
}

void AChromosome::Mutation()
{

	int round = Cast<AActionGameState>(GetWorld()->GetGameState())->GetRound();

	//Igual dividir el maximo por un numero acordado menos la ronda
	genesArray[0] = FMath::RandRange(1, 1 * round); //10
	genesArray[3] = FMath::FRandRange(0.f, 5 * round); //100

	genesArray[4] = FMath::FRandRange(0.f, 500 * round); //300
	genesArray[5] = FMath::FRandRange(0.f, 1000 * round); //400
	genesArray[6] = FMath::FRandRange(0.f, 1000 * round); //400
	genesArray[7] = FMath::FRandRange(0.f, 200 * round); //1000
	genesArray[8] = FMath::FRandRange(0.f, 200 * round); //1000
	genesArray[9] = FMath::FRandRange(0.f, 20 * round); //50
	genesArray[10] = FMath::FRandRange(0.f, 20 * round); //100
	genesArray[11] = FMath::FRandRange(0.f, (2 * round)%100); //100
}

AChromosome* AChromosome::Clone()
{

	AChromosome* clonedChromosome = GetWorld()->SpawnActor<AChromosome>();
	/*
	clonedChromosome->SetSizeGene(sizeGene);
	clonedChromosome->SetDamageCausedTopTarget(damageCausedToTarget);
	clonedChromosome->SetTimeAlive(timeAlive);
	clonedChromosome->SetImpactDamage(impactDamage);

	clonedChromosome->SetSpeedDropRate(speedDropRate);
	clonedChromosome->SetDefaultMaxAcceleration(defaultMaxAcceleration);
	clonedChromosome->SetMaxAcceleration(maxAcceleration);
	clonedChromosome->SetDefaultMaxSpeed(defaultMaxSpeed);
	clonedChromosome->SetMaxSpeed(maxSpeed);
	clonedChromosome->SetAccelerationSpeed(accelerationSpeed);
	clonedChromosome->SetDecelerationSpeed(decelerationSpeed);
	clonedChromosome->SetManeuverabilityInPercent(maneuverabilityInPercent);
	*/
	clonedChromosome->SetGenesArray(genesArray);

	return clonedChromosome;
}

void AChromosome::SetDamageCausedTopTarget(float amount)
{

	genesArray[2] = amount;
}

float AChromosome::GetDamageCausedToTarget()
{

	return genesArray[2];
}

void AChromosome::AddDamageCausedToTarget(float amount)
{

	genesArray[2] += amount;
}

float AChromosome::GetTimeAlive()
{

	return genesArray[1];
}

void AChromosome::SetTimeAlive(float time)
{

	genesArray[1] = time;
}

float AChromosome::GetImpactDamage()
{

	return genesArray[3];
}

void AChromosome::SetImpactDamage(float damage)
{

	genesArray[3] = damage;
}

float AChromosome::GetSpeedDropRate()
{
	return genesArray[4];
}

void AChromosome::SetSpeedDropRate(float value)
{

	genesArray[4] = value;
}

float AChromosome::GetDefaultMaxAcceleration()
{

	return genesArray[5];
}

void AChromosome::SetDefaultMaxAcceleration(float value)
{

	genesArray[5] = value;
}

float AChromosome::GetMaxAcceleration()
{

	return genesArray[6];
}

void AChromosome::SetMaxAcceleration(float value)
{

	genesArray[6] = value;
}

float AChromosome::GetDefaultMaxSpeed()
{

	return genesArray[7];
}

void AChromosome::SetDefaultMaxSpeed(float value)
{

	genesArray[7] = value;
}

float AChromosome::GetMaxSpeed()
{

	return genesArray[8];
}

void AChromosome::SetMaxSpeed(float value)
{

	genesArray[8] = value;
}

float AChromosome::GetAccelerationSpeed()
{

	return genesArray[9];
}

void AChromosome::SetAccelerationSpeed(float value)
{

	genesArray[9] = value;
}

float AChromosome::GetDecelerationSpeed()
{

	return genesArray[10];
}

void AChromosome::SetDecelerationSpeed(float value)
{

	genesArray[10] = value;
}

float AChromosome::GetManeuverabilityInPercent()
{

	return genesArray[11];
}

void AChromosome::SetManeuverabilityInPercent(float value)
{

	genesArray[11] = value;
}

void AChromosome::SetbAlive(bool value)
{

	bAlive = value;
}

void AChromosome::SetGenesArray(TArray<float> genes)
{

	genesArray.Empty();

	for(int i = 0; i < genes.Num(); i++)
	{

		genesArray.Add(genes[i]);
	}
}

void AChromosome::ApplyFenotipe()
{

	AActor* myOwner = GetOwner();

	if(myOwner)
		myOwner->SetActorScale3D(FVector(genesArray[0]));
}

void AChromosome::ApplyMovementGenes()
{

	AEnemyActionPawn* myOwner = Cast<AEnemyActionPawn>(GetOwner());

	if (myOwner)
	{

		myOwner->InitMovementCompnent(genesArray[4], genesArray[5], genesArray[7], genesArray[6], genesArray[8], genesArray[9], genesArray[10], genesArray[11]);

	}
}

// Called when the game starts or when spawned
void AChromosome::BeginPlay()
{
	Super::BeginPlay();

	//mientras no encuentre como reservar y inicializar n elementos en declaracion de TArray lo hago manual
	int numGenes = 12;
	for(int i = 0; i < numGenes; i++)
	{

		genesArray.Push(0.f);
	}

}

// Called every frame
void AChromosome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bAlive)
		genesArray[1] += DeltaTime;

}
