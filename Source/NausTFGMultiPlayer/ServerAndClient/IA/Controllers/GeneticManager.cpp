// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneticManager.h"

#include "AIBaseController.h"
#include "EnemyManager.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"

// Sets default values
AGeneticManager::AGeneticManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	bAlwaysRelevant = true;

}

// Called when the game starts or when spawned
void AGeneticManager::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AGeneticManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

TArray<AChromosome*> AGeneticManager::GenerateNextGenerationDna(TArray<AChromosome*> actualGenerationDNA)
{

	TArray<AChromosome*> DNAResult;

	for (int i = 0; i < 50; i++)
	{

		AChromosome* DNA = GetWorld()->SpawnActor<AChromosome>();
		DNA->SetRandomGenes();

		DNAResult.Add(DNA);

	}

	return DNAResult;
}

