// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneticManager.h"

#include "AIBaseController.h"
#include "EnemyManager.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"
#include "cmath"
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
	TArray<AChromosome*> DNABestIndividues;

	{

		//Obtiene mejores individuos
		DNABestIndividues = GetBestIndividues(actualGenerationDNA, (actualGenerationDNA.Num()+1)/2);

		//Los cruzo (de momento) haciendo que el mejor se reproduzca con todos los mejores
		for(int i = 0; i < 1; i++)
		{

			for(int j = 0; j < DNABestIndividues.Num(); ++j)
			{

				AChromosome* son = CrossOver(DNABestIndividues[i], DNABestIndividues[j]);

				DNAResult.Add(son);

			}

		}

	}

	return DNAResult;
}

TArray<AChromosome*> AGeneticManager::GenerateFirstGenerationDna()
{
	TArray<AChromosome*> DNAResult;

	int populationSize = 1;

	//En caso de primera iteracion o de eliminados todos por el jugador (de momento)
	//Crea nueva generacion
	for (int i = 0; i < populationSize; i++)
	{

		AChromosome* DNA = GetWorld()->SpawnActor<AChromosome>();

		//Por si ha intentado spawnear en un lugar donde habia colision y no se ha finalizado el proceso
		if (!DNA)
		{

			i--;
			continue;
		}

		DNA->SetRandomGenes();

		DNAResult.Add(DNA);

	}

	return DNAResult;

}

AChromosome* AGeneticManager::CrossOver(AChromosome* parent1, AChromosome* parent2)
{

	float probabilityCrossOver = (rand() % 100) + 1;

	AChromosome* son = GetWorld()->SpawnActor<AChromosome>();

	son->SetSizeGene(parent2->GetSizeGene());

	if(probabilityCrossOver < 60)
	{
		
		son->SetSizeGene(parent1->GetSizeGene());
	}

	float probabilityMutation = (rand() % 100) + 1;

	if(probabilityMutation < 5)
	{

		son->Mutation();
	}

	return son;
}

float AGeneticManager::CalculateAptitude(AChromosome* individual)
{

	return individual->GetSizeGene().Size() + individual->GetTimeAlive() + individual->GetDamageCausedToTarget();
}

TArray<AChromosome*> AGeneticManager::GetBestIndividues(TArray<AChromosome*> population, int32 numIndividues)
{

	TArray<AChromosome*> ResultDNA;

	//Definido por la aptitud y el indice en el vector population
	TArray< TPair<float, int> > Candidates;

	Candidates.Reserve(numIndividues);

	for(int j = 0; j < population.Num(); j++)
	{
		auto x = population[j];

		float aptitude = CalculateAptitude(x);

		//fuera de rango en el caso de ser peor que los n mejores
		int index = numIndividues + 1;

		//Buscamos posicion
		for (int i = 0; i < Candidates.Num(); i++)
		{

			if (Candidates[i].Key < aptitude)
			{

				index = i;
				break;
			}
		}

		if(index > numIndividues)
		{

			Candidates.Add(TPair<float, int>(aptitude, j));
		}else
		{

			Candidates.Insert(TPair<float, int>(aptitude, j), index);
		}

	}

	ResultDNA.Reserve(numIndividues);

	//Creamos el resultado
	for(int i = 0; i < numIndividues; i++)
	{

		ResultDNA.Add(population[Candidates[i].Value]);
	}

	return ResultDNA;

}

