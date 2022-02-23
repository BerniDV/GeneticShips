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
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	bAlwaysRelevant = true;

}

// Called when the game starts or when spawned
void AGeneticManager::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{

		GetWorld()->GetTimerManager().SetTimer(timerHandler, this, &AGeneticManager::SpawnEnemies, 20.f, true);

	}
		
	
}

// Called every frame
void AGeneticManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AGeneticManager::SpawnEnemies()
{
	int numEnemies = 100.f;

	DestroyAllADN();

	for (int i = 0; i < numEnemies; i++)
	{

		AChromosome* DNA = GetWorld()->SpawnActor<AChromosome>();
		DNA->SetRandomGenes();

		nextGenerationDNA.Add(DNA);

	}

	//Pasar como parametro el array de adn de todos los nuevos enemigos
	enemyManager->SpawnEnemies(nextGenerationDNA);

}

void AGeneticManager::SetEnemyManager(AEnemyManager* enemyMG)
{

	enemyManager = enemyMG;
}

void AGeneticManager::DestroyAllADN()
{

	for(auto x: nextGenerationDNA)
	{

		x->Destroy();
	}

	nextGenerationDNA.Empty();
}

