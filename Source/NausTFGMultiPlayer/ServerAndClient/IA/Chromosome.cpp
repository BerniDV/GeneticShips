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

	timeAlive = 0.f;
	damageCausedToTarget = 0.f;
	impactDamage = 0.f;
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
	impactDamage = FMath::FRandRange(0.f, 25.f);

	speedDropRate = FMath::FRandRange(0.f, 100.f);
	defaultMaxAcceleration = FMath::FRandRange(0.f, 100.f);
	maxAcceleration = FMath::FRandRange(0.f, 100.f);
	defaultMaxSpeed = FMath::FRandRange(0.f, 100.f);
	maxSpeed = FMath::FRandRange(0.f, 100.f);
	accelerationSpeed = FMath::FRandRange(0.f, 50.f);
	decelerationSpeed = FMath::FRandRange(0.f, 100.f);
	maneuverabilityInPercent = FMath::FRandRange(0.f, 10.f);
}

void AChromosome::Mutation()
{

	int round = Cast<AActionGameState>(GetWorld()->GetGameState())->GetRound();

	//Igual dividir el maximo por un numero acordado menos la ronda
	sizeGene = FVector(FMath::RandRange(1, 1 * round)); //10
	impactDamage = FMath::FRandRange(0.f, 5 * round); //100

	speedDropRate = FMath::FRandRange(0.f, 500 * round); //300
	defaultMaxAcceleration = FMath::FRandRange(0.f, 1000 * round); //400
	maxAcceleration = FMath::FRandRange(0.f, 1000 * round); //400
	defaultMaxSpeed = FMath::FRandRange(0.f, 200 * round); //1000
	maxSpeed = FMath::FRandRange(0.f, 200 * round); //1000
	accelerationSpeed = FMath::FRandRange(0.f, 20 * round); //50
	decelerationSpeed = FMath::FRandRange(0.f, 20 * round); //100
	maneuverabilityInPercent = FMath::FRandRange(0.f, (2 * round)%100); //100
}

AChromosome* AChromosome::Clone()
{

	AChromosome* clonedChromosome = GetWorld()->SpawnActor<AChromosome>();

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

float AChromosome::GetImpactDamage()
{

	return impactDamage;
}

void AChromosome::SetImpactDamage(float damage)
{

	impactDamage = damage;
}

float AChromosome::GetSpeedDropRate()
{
	return speedDropRate;
}

void AChromosome::SetSpeedDropRate(float value)
{

	speedDropRate = value;
}

float AChromosome::GetDefaultMaxAcceleration()
{

	return defaultMaxAcceleration;
}

void AChromosome::SetDefaultMaxAcceleration(float value)
{

	defaultMaxAcceleration = value;
}

float AChromosome::GetMaxAcceleration()
{

	return maxAcceleration;
}

void AChromosome::SetMaxAcceleration(float value)
{

	maxAcceleration = value;
}

float AChromosome::GetDefaultMaxSpeed()
{

	return defaultMaxSpeed;
}

void AChromosome::SetDefaultMaxSpeed(float value)
{

	defaultMaxSpeed = value;
}

float AChromosome::GetMaxSpeed()
{

	return maxSpeed;
}

void AChromosome::SetMaxSpeed(float value)
{

	maxSpeed = value;
}

float AChromosome::GetAccelerationSpeed()
{

	return accelerationSpeed;
}

void AChromosome::SetAccelerationSpeed(float value)
{

	accelerationSpeed = value;
}

float AChromosome::GetDecelerationSpeed()
{

	return decelerationSpeed;
}

void AChromosome::SetDecelerationSpeed(float value)
{

	decelerationSpeed = value;
}

float AChromosome::GetManeuverabilityInPercent()
{

	return maneuverabilityInPercent;
}

void AChromosome::SetManeuverabilityInPercent(float value)
{

	maneuverabilityInPercent = value;
}

void AChromosome::ApplyFenotipe()
{

	AActor* myOwner = GetOwner();

	if(myOwner)
		myOwner->SetActorScale3D(sizeGene);
}

void AChromosome::ApplyMovementGenes()
{

	AEnemyActionPawn* myOwner = Cast<AEnemyActionPawn>(GetOwner());

	if (myOwner)
	{

		myOwner->InitMovementCompnent(speedDropRate, defaultMaxAcceleration, defaultMaxSpeed, maxAcceleration, maxSpeed, accelerationSpeed, decelerationSpeed, maneuverabilityInPercent);

	}
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

