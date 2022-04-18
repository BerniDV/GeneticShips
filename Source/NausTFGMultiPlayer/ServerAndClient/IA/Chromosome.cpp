// Fill out your copyright notice in the Description page of Project Settings.


#include "Chromosome.h"

#include "ParameterCollection.h"
#include "Controllers/AIBaseController.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AChromosome::AChromosome()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false;
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


void AChromosome::SetRandomGenes()
{

	genesArray[(int8)Gene::color] = FMath::FRandRange(0, 1);
	genesArray[(int8)Gene::color + 1] = FMath::FRandRange(0, 1);
	genesArray[(int8)Gene::color + 2] = FMath::FRandRange(0, 1);

	genesArray[(int8)Gene::size] = FMath::RandRange(1, 10);
	genesArray[(int8)Gene::impactDamage] = FMath::FRandRange(1.f, 25.f);
	genesArray[(int8)Gene::bulletDamage] = FMath::FRandRange(1.f, 25.f);

	genesArray[(int8)Gene::speedDropRate] = FMath::FRandRange(0.f, 1000.f);
	genesArray[(int8)Gene::defaultMaxAcceleration] = FMath::FRandRange(0.f, 1000.f);
	genesArray[(int8)Gene::maxAcceleration] = FMath::FRandRange(0.f, 1000.f);
	genesArray[(int8)Gene::defaultMaxSpeed] = FMath::FRandRange(0.f, 1000.f);
	genesArray[(int8)Gene::maxSpeed] = FMath::FRandRange(0.f, 1000.f);
	genesArray[(int8)Gene::accelerationSpeed] = FMath::FRandRange(0.f, 500.f);
	genesArray[(int8)Gene::decelerationSpeed] = FMath::FRandRange(0.f, 1000.f);
	genesArray[(int8)Gene::maneuverabilityInPercent] = FMath::FRandRange(0.f, 100.f);
	genesArray[(int8)Gene::fireCadancy] = FMath::FRandRange(5.f, 10.f);
	genesArray[(int8)Gene::health] = FMath::FRandRange(1.f, 100.f);
}

void AChromosome::Mutation()
{

	int round = Cast<AActionGameState>(GetWorld()->GetGameState())->GetRound();

	//Igual dividir el maximo por un numero acordado menos la ronda

	genesArray[(int8)Gene::size] = FMath::RandRange(10, (1 * round) % 100); //10
	genesArray[(int8)Gene::impactDamage] = FMath::FRandRange(0.f, (5 * round) % 100); //100
	genesArray[(int8)Gene::bulletDamage] = FMath::FRandRange(0.f, (5 * round) % 100); //100

	genesArray[(int8)Gene::speedDropRate] = FMath::FRandRange(0.f, (5000 * round) % 100000); //300
	genesArray[(int8)Gene::defaultMaxAcceleration] = FMath::FRandRange(0.f, (10000 * round)%200000); //400
	genesArray[(int8)Gene::maxAcceleration] = FMath::FRandRange(0.f, (10000 * round) % 200000); //400
	genesArray[(int8)Gene::defaultMaxSpeed] = FMath::FRandRange(0.f, (2000 * round) % 40000); //1000
	genesArray[(int8)Gene::maxSpeed] = FMath::FRandRange(0.f, (2000 * round) % 40000); //1000
	genesArray[(int8)Gene::accelerationSpeed] = FMath::FRandRange(0.f, (200 * round) % 4000); //50
	genesArray[(int8)Gene::decelerationSpeed] = FMath::FRandRange(0.f, (200 * round) % 4000); //100
	genesArray[(int8)Gene::maneuverabilityInPercent] = FMath::FRandRange(0.f, (2 * round) % 100); //100
	genesArray[(int8)Gene::fireCadancy] = FMath::FRandRange(0.1f, (1 * round + 1) % 20); //0.1
	genesArray[(int8)Gene::fireCadancy] = 1.f / genesArray[12];
	genesArray[(int8)Gene::health] = FMath::FRandRange(1.f, (100 * round) % 1000);
}

AChromosome* AChromosome::Clone()
{

	AChromosome* clonedChromosome = GetWorld()->SpawnActor<AChromosome>();

	clonedChromosome->SetGenesArray(genesArray);

	return clonedChromosome;
}

void AChromosome::SetGenesArray(TArray<float> genes)
{

	genesArray.Empty();

	for (int i = 0; i < genes.Num(); i++)
	{

		genesArray.Add(genes[i]);
	}
}

void AChromosome::SetGene(Gene typeGene, float value)
{

	genesArray[(int8)typeGene] = value;
}

float AChromosome::GetGene(Gene typeGene)
{

	return genesArray[(int8)typeGene];
}

void AChromosome::AddToGene(Gene typeGene, float amount)
{

	genesArray[(int8)typeGene] += amount;
}

void AChromosome::ApplyFenotipe()
{

	ApplyFenotipeSize(FVector(genesArray[(int8)Gene::size]));
	ApplyFenotipeColor(FLinearColor(genesArray[(int8)Gene::color], genesArray[(int8)Gene::color + 1], genesArray[(int8)Gene::color + 2]));
}

void AChromosome::ApplyFenotipeSize(FVector size)
{

	if(AActionPawn* myPawn = Cast<AActionPawn>(GetOwner()))
	{

		FVector normalSize = FVector(52.f, 3.f, 7.f);

		myPawn->SetActorScale3D(size * normalSize);
		myPawn->SetSizeAllClients(size * normalSize);
	}
}

void AChromosome::ApplyFenotipeColor(FLinearColor color)
{

	if (AEnemyActionPawn* myPawn = Cast<AEnemyActionPawn>(GetOwner()))
	{

		myPawn->SetEmissiveColor(color);
		myPawn->SetColorAllClients(color);

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

void AChromosome::ApplyHealthGenes()
{

	AEnemyActionPawn* myOwner = Cast<AEnemyActionPawn>(GetOwner());

	if (myOwner && myOwner->HasAuthority())
	{

		AAIBaseController* myController = myOwner->GetController<AAIBaseController>();


		if(myController)
		{

			myController->SetHealth(genesArray[(int8)Gene::health]);
		}

	}
}

// Called when the game starts or when spawned
void AChromosome::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{

		for (int i = 0; i < numGenes; i++)
		{

			genesArray.Push(0.f);
		}
	}
	
}

// Called every frame
void AChromosome::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAlive && HasAuthority())
		genesArray[(int8)Gene::timeAlive] += DeltaTime;

}

