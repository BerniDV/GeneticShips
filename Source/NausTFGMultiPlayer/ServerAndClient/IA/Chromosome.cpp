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

	

}

void AChromosome::Destroyed()
{
	Super::Destroyed();

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Chromosome Destroyed"));
}

FVector AChromosome::GetSizeGene()
{

	return FVector(genesArray[(int8)Gene::size]);
}

void AChromosome::SetSizeGene(FVector SizeGene)
{

	genesArray[(int8)Gene::size] = SizeGene.X;
	
}

void AChromosome::SetRandomGenes()
{
	genesArray[(int8)Gene::size] = FMath::RandRange(1, 1);
	genesArray[(int8)Gene::impactDamage] = FMath::FRandRange(0.f, 25.f);

	genesArray[(int8)Gene::speedDropRate] = FMath::FRandRange(0.f, 100.f);
	genesArray[(int8)Gene::defaultMaxAcceleration] = FMath::FRandRange(0.f, 100.f);
	genesArray[(int8)Gene::maxAcceleration] = FMath::FRandRange(0.f, 100.f);
	genesArray[(int8)Gene::defaultMaxSpeed] = FMath::FRandRange(0.f, 100.f);
	genesArray[(int8)Gene::maxSpeed] = FMath::FRandRange(0.f, 100.f);
	genesArray[(int8)Gene::accelerationSpeed] = FMath::FRandRange(0.f, 50.f);
	genesArray[(int8)Gene::decelerationSpeed] = FMath::FRandRange(0.f, 100.f);
	genesArray[(int8)Gene::maneuverabilityInPercent] = FMath::FRandRange(0.f, 10.f);
	genesArray[(int8)Gene::fireCadancy] = FMath::FRandRange(5.f, 10.f);
}

void AChromosome::Mutation()
{

	int round = Cast<AActionGameState>(GetWorld()->GetGameState())->GetRound();

	//Igual dividir el maximo por un numero acordado menos la ronda
	genesArray[(int8)Gene::size] = FMath::RandRange(1, 1 * round); //10
	genesArray[(int8)Gene::impactDamage] = FMath::FRandRange(0.f, 5 * round); //100

	genesArray[(int8)Gene::speedDropRate] = FMath::FRandRange(0.f, 500 * round); //300
	genesArray[(int8)Gene::defaultMaxAcceleration] = FMath::FRandRange(0.f, 1000 * round); //400
	genesArray[(int8)Gene::maxAcceleration] = FMath::FRandRange(0.f, 1000 * round); //400
	genesArray[(int8)Gene::defaultMaxSpeed] = FMath::FRandRange(0.f, 200 * round); //1000
	genesArray[(int8)Gene::maxSpeed] = FMath::FRandRange(0.f, 200 * round); //1000
	genesArray[(int8)Gene::accelerationSpeed] = FMath::FRandRange(0.f, 20 * round); //50
	genesArray[(int8)Gene::decelerationSpeed] = FMath::FRandRange(0.f, 20 * round); //100
	genesArray[(int8)Gene::maneuverabilityInPercent] = FMath::FRandRange(0.f, (2 * round)%100); //100
	genesArray[(int8)Gene::fireCadancy] = FMath::FRandRange(0.1f, (1 * round + 1)%20); //0.1
	genesArray[(int8)Gene::fireCadancy] = 1.f / genesArray[12];
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

float AChromosome::GetGene(Gene gene)
{

	return genesArray[(int8)gene];
}

void AChromosome::SetGene(Gene gene, float value)
{

	genesArray[(int8)gene] = value;
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

	ApplyFenotipeSize(FVector(genesArray[(int8)Gene::size]));
}

void AChromosome::ApplyFenotipeSize(FVector size)
{

	if (AActionPawn* myPawn = Cast<AActionPawn>(GetOwner()))
	{

		myPawn->SetActorScale3D(size);
		myPawn->SetSizeAllClients(size);
	}
}

void AChromosome::ApplyMovementGenes()
{

	AEnemyActionPawn* myOwner = Cast<AEnemyActionPawn>(GetOwner());

	if (myOwner)
	{

		myOwner->InitMovementCompnent(genesArray[(int8)Gene::speedDropRate], genesArray[(int8)Gene::defaultMaxAcceleration], genesArray[(int8)Gene::defaultMaxSpeed], genesArray[(int8)Gene::maxAcceleration], genesArray[(int8)Gene::maxSpeed], genesArray[(int8)Gene::accelerationSpeed], genesArray[(int8)Gene::decelerationSpeed], genesArray[(int8)Gene::maneuverabilityInPercent]);

	}
}

// Called when the game starts or when spawned
void AChromosome::BeginPlay()
{
	Super::BeginPlay();

	//mientras no encuentre como reservar y inicializar n elementos en declaracion de TArray lo hago manual
	
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
		genesArray[(int8)Gene::timeAlive] += DeltaTime;

}
/*
	 * 0: size
	 * 1: timeAlive
	 * 2: damageCaused
	 * 3: impactDamage
	 * 4: speedDropRate
	 * 5: defaultMaxAcceleration
	 * 6: maxAcceleration
	 * 7: defaultMaxSpeed
	 * 8: maxSpeed
	 * 9: accelerationSpeed
	 * 10: decelerationSpeed
	 * 11: maneuverabilityInPercent
	 * 12: fireCadancy
	 */