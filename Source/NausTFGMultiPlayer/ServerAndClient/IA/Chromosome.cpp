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

	genesArray[(int8)Gene::color1] = FMath::FRandRange(0, 1);
	genesArray[(int8)Gene::color2] = FMath::FRandRange(0, 1);
	genesArray[(int8)Gene::color3] = FMath::FRandRange(0, 1);

	genesArray[(int8)Gene::size] = FMath::RandRange(1, 10);
	genesArray[(int8)Gene::impactDamage] = FMath::FRandRange(15.f, 50.f);
	genesArray[(int8)Gene::bulletDamage] = FMath::FRandRange(15.f, 50.f);

	genesArray[(int8)Gene::speedDropRate] = FMath::FRandRange(0.f, 1000.f);
	genesArray[(int8)Gene::defaultMaxAcceleration] = FMath::FRandRange(1000.f / 4.f, 1000.f / 4.f);
	genesArray[(int8)Gene::maxAcceleration] = FMath::FRandRange(1000.f / 4.f, 4000.f / 4.f);
	genesArray[(int8)Gene::defaultMaxSpeed] = FMath::FRandRange(1000.f / 4.f, 4000.f / 4.f);
	genesArray[(int8)Gene::maxSpeed] = FMath::FRandRange(30000.f/4.f, 7000.f / 4.f);
	genesArray[(int8)Gene::accelerationSpeed] = FMath::FRandRange(500.f / 4.f, 2000.f / 4.f);
	genesArray[(int8)Gene::decelerationSpeed] = FMath::FRandRange(0.f, 1000.f / 4.f);
	genesArray[(int8)Gene::maneuverabilityInPercent] = FMath::FRandRange(0.f, 50.f);
	genesArray[(int8)Gene::fireCadancy] = FMath::FRandRange(0.5f, 6.f);
	genesArray[(int8)Gene::health] = FMath::FRandRange(100.f, 300.f);
}

void AChromosome::Mutation()
{

	int round = Cast<AActionGameState>(GetWorld()->GetGameState())->GetRound();

	int numGenesToMutate = FMath::RandRange(0, numGenes/4);

	for(int i = 0; i < numGenesToMutate; i++)
	{

		int geneToMutate = FMath::RandRange(0, numGenes - 1);

		switch (geneToMutate)
		{

		case 3:

			genesArray[(int8)Gene::impactDamage] = FMath::FRandRange(0.f, (5 * round) % maxImpactDamage); //100

			break;

		case 4:

			genesArray[(int8)Gene::speedDropRate] = FMath::FRandRange(0.f, (5000 * round) % maxSpeedDropRate); //300
			break;

		case 5:

			genesArray[(int8)Gene::defaultMaxAcceleration] = FMath::FRandRange(0.f, (10000 * round) % maxDefaultMaxAcceleration); //400
			break;
		case 6:

			genesArray[(int8)Gene::maxAcceleration] = FMath::FRandRange(0.f, (10000 * round) % maxMaxAcceleration); //400
			break;

		case 7:

			genesArray[(int8)Gene::defaultMaxSpeed] = FMath::FRandRange(0.f, (2000 * round) % maxdefaultMaxSpeed); //1000
			break;
		case 8:

			genesArray[(int8)Gene::maxSpeed] = FMath::FRandRange(0.f, (2000 * round) % maxMaxSpeed); //1000
			
			break;

		case 9:

			genesArray[(int8)Gene::accelerationSpeed] = FMath::FRandRange(0.f, (200 * round) % maxAccelerationSpeed); //50
			break;
		case 10:

			genesArray[(int8)Gene::decelerationSpeed] = FMath::FRandRange(0.f, (200 * round) % maxDecelerationSpeed); //100
			
			break;

		case 11:

			genesArray[(int8)Gene::maneuverabilityInPercent] = FMath::FRandRange(0.f, (2 * round) % maxManeuverabilityInPercent); //100
			break;

		case 12:

			genesArray[(int8)Gene::fireCadancy] = FMath::FRandRange(0.1f, (1 * round + 1) % maxFireCadancy); //0.1
			genesArray[(int8)Gene::fireCadancy] = 1.f / genesArray[12];
			break;

		case 16:

			genesArray[(int8)Gene::health] = FMath::FRandRange(1.f, (100 * round) % maxHealth);
			break;

		case 17:

			genesArray[(int8)Gene::bulletDamage] = FMath::FRandRange(0.f, (5 * round) % maxBulletDamage); //100
			break;

		default:

			numGenesToMutate--;
			break;
		}

	}
	/*
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
	*/
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

int AChromosome::GetNumGenes()
{

	return numGenes;
}

void AChromosome::SetGene(Gene typeGene, float value)
{

	genesArray[(int8)typeGene] = value;
}

void AChromosome::SetGene(int indexGene, float value)
{

	genesArray[indexGene] = value;
}


float AChromosome::GetGene(Gene typeGene)
{

	return genesArray[(int8)typeGene];
}

float AChromosome::GetGene(int indexGene)
{

	return genesArray[indexGene];
}

void AChromosome::AddToGene(Gene typeGene, float amount)
{

	genesArray[(int8)typeGene] += amount;
}

void AChromosome::ApplyFenotipe()
{

	ApplyFenotipeSize(FVector(genesArray[(int8)Gene::size]));
	ApplyFenotipeColor(FLinearColor(genesArray[(int8)Gene::color1], genesArray[(int8)Gene::color2], genesArray[(int8)Gene::color3]));
}

void AChromosome::ApplyFenotipeSize(FVector size)
{

	float resultSize;

	if(AActionPawn* myPawn = Cast<AActionPawn>(GetOwner()))
	{

		FVector normalSize = FVector(52.f, 3.f, 7.f) * 5;
		//normalSize.Normalize();
		//normalSize *= 10;

		//calcular tamany

		float relativeHealth = (genesArray[(int8)Gene::health] / maxHealth);
		float relativeBulletDamage = (genesArray[(int8)Gene::bulletDamage] / maxBulletDamage);
		float relativeImpactDamage = (genesArray[(int8)Gene::impactDamage] / maxImpactDamage);
		float relativeVelocity = (genesArray[(int8)Gene::maxSpeed] / maxMaxSpeed);
		float relativeManeuverability = (genesArray[(int8)Gene::maneuverabilityInPercent] / maxManeuverabilityInPercent);
		float relativeCadency = (genesArray[(int8)Gene::fireCadancy] / maxFireCadancy);
		float parentSize = (genesArray[(int8)Gene::size] / maxSize);

		resultSize = ((0.6 * relativeHealth) + (0.2 * relativeImpactDamage) + (0.2 * relativeBulletDamage)) - ((0.5 * relativeManeuverability) + (0.2 * relativeCadency) + (0.3 * relativeVelocity));

		resultSize += 1;
		
		myPawn->SetActorScale3D(resultSize * normalSize);
		myPawn->SetSizeAllClients(resultSize * normalSize);
	}
}

void AChromosome::ApplyFenotipeColor(FLinearColor color)
{

	if (AEnemyActionPawn* myPawn = Cast<AEnemyActionPawn>(GetOwner()))
	{

		float red;
		float green;
		float blue;

		//Calcula color

		float relativeHealth = (genesArray[(int8)Gene::health] / maxHealth);
		float relativeBulletDamage = (genesArray[(int8)Gene::bulletDamage] / maxBulletDamage);
		float relativeImpactDamage = (genesArray[(int8)Gene::impactDamage] / maxImpactDamage);
		float relativeVelocity = (genesArray[(int8)Gene::maxSpeed] / maxMaxSpeed);
		float relativeManeuverability = (genesArray[(int8)Gene::maneuverabilityInPercent] / maxManeuverabilityInPercent);
		float relativeCadency = (genesArray[(int8)Gene::fireCadancy] / maxFireCadancy);
		float parentSize = (genesArray[(int8)Gene::size] / maxSize);

		red = ((0.6 * relativeImpactDamage) + (0.4 * relativeBulletDamage));
		green = ((0.5 * relativeCadency) + (0.5 * relativeHealth));
		blue = ((0.7 * relativeVelocity) + (0.3 * relativeManeuverability));

		FLinearColor resultColor(red, green, blue);

		myPawn->SetEmissiveColor(resultColor);
		myPawn->SetColorAllClients(resultColor);

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

	if (bAlive && HasAuthority() && GetOwner())
	{

		genesArray[(int8)Gene::timeAlive] += DeltaTime;

	}
		

}

