// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActionPawn.h"

#include "Components/BoxComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"
#include "Net/UnrealNetwork.h"

AEnemyActionPawn::AEnemyActionPawn()
{
	
	bReplicates = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	RootComponent = boxComponent;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

	enemyChromosome = nullptr;

	id = -1;
}

void AEnemyActionPawn::SetID(int32 newEnemyID)
{

	id = newEnemyID;
}



void AEnemyActionPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnemyActionPawn, enemyChromosome);
}

void AEnemyActionPawn::SetRandomGenes()
{

	enemyChromosome->SetRandomGenes();
}

void AEnemyActionPawn::ApplyFenotipe()
{

	enemyChromosome->ApplyFenotipe();
}

void AEnemyActionPawn::SetChromosome(AChromosome* newChromosome)
{

	enemyChromosome = newChromosome;

	ApplyFenotipe();
}

void AEnemyActionPawn::BeginPlay()
{
	Super::BeginPlay();
		

}

void AEnemyActionPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

		
}

void AEnemyActionPawn::Destroyed()
{
	
	//enemyChromosome->Destroy();

	Super::Destroyed();

}
