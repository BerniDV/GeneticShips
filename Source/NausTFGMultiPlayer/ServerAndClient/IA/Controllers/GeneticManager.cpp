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

	populationSize = 0;

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
	TArray<AChromosome*> DNAParents;

	{

		//Obtiene mejores individuos
		//DNABestIndividues = GetBestIndividues(actualGenerationDNA, (actualGenerationDNA.Num()+1)/2);

		//Calcula valor de aptitud de los individuos y de la poblacion

		TArray<float> aptitudes;

		float aptitudePopulation = CalculateRelativeAptitudes(aptitudes, actualGenerationDNA);



		//Metodo de la ruleta (seleccion de montecarlo): Calcular la aptitud relativa al grupo y usarla como probabilidad, se tira la ruleta y se escoge como padre la region en la que cae.
		for (int i = 0; i < aptitudes.Num(); i++)
		{

			float rulete = FMath::FRandRange(0.f, 1.f);

			DNAParents.Add(actualGenerationDNA[GetIndexChromosomeRulete(aptitudes, rulete)]);

		}

		for (int j = 0; j < DNAParents.Num(); ++j)
		{
			AChromosome* son = CrossOver(DNAParents[0], DNAParents[j]);

			DNAResult.Add(son);
		}

	}

	return DNAResult;
}

float AGeneticManager::CalculateRelativeAptitudes(TArray<float>& aptitudes, TArray<AChromosome*> population)
{

	float aptitudePopulation = 0.f;

	for (auto x : population)
	{

		float aptitude = CalculateAptitude(x);
		aptitudePopulation += aptitude;

		aptitudes.Add(CalculateAptitude(x));
	}

	for (int i = 0; i < aptitudes.Num(); i++)
	{

		aptitudes[i] = aptitudes[i] / aptitudePopulation;
	}

	return aptitudePopulation;
}

TArray<AChromosome*> AGeneticManager::GenerateFirstGenerationDna()
{
	TArray<AChromosome*> DNAResult;

	if (populationSize == 0)
		populationSize = 100;

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

	//float probabilityCrossOver = (rand() % 100) + 1;

	AChromosome* son = GetWorld()->SpawnActor<AChromosome>();

	//Aqui aplicare diferentes metodos de crossover como de doble punto etc...
	//De momento aplico un punto
	int point = FMath::RandRange(0, parent1->GetNumGenes());

	/*
	if(probabilityCrossOver < 60)
	{
		
		son = parent1->Clone();

	}else
	{

		son = parent2->Clone();
	}*/

	for(int i = 0; i < point; i++)
	{

		son->SetGene(i, parent1->GetGene(i));
	}

	for (int i = point; i < parent1->GetNumGenes(); i++)
	{

		son->SetGene(i, parent2->GetGene(i));
	}

	float probabilityMutation = (rand() % 100) + 1;

	if(probabilityMutation < 15)
	{

		son->Mutation();
	}

	son->SetGene(Gene::traveledDistance, 0.f);
	son->SetGene(Gene::damageCaused, 0.f);
	son->SetGene(Gene::timeAlive, 0.f);


	return son;
}

float AGeneticManager::CalculateAptitude(AChromosome* individual)
{

	//No mes temps viud -> si mes temps aporp meu, 
	return individual->GetGene(Gene::timeAlive) * 0 + individual->GetGene(Gene::damageCaused) * 1 + individual->GetGene(Gene::traveledDistance) * 0 + individual->GetGene(Gene::bulletDamage) * 0;
}

void AGeneticManager::SetPopulationSize(int population)
{

	populationSize = population;
}

int AGeneticManager::GetIndexChromosomeRulete(TArray<float> aptitudes, float rulete)
{

	int index;

	float amountProbabilities = 0.f;

	//crear un altre vector amb info de aptitud i index associat per calcular la ruleta amb ell i retornar el index correcte
	TArray<TPair<float, int>> aptitudeIndexArray;

	for(int i = 0; i < aptitudes.Num(); i++)
	{

		aptitudeIndexArray.Add(TPair<float, int>(aptitudes[i], i));
	}

	aptitudeIndexArray.Sort([](TPair<float, int> a, TPair<float, int> b) { return a.Key > b.Key; });

	for (int i = 0; i < aptitudeIndexArray.Num(); i++)
	{

		amountProbabilities += aptitudeIndexArray[i].Key;

		if (amountProbabilities >= rulete)
		{

			index = aptitudeIndexArray[i].Value;
			return index;
		}
	}

	//No deberiamos llegar nunca aqui
	return -1;
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

