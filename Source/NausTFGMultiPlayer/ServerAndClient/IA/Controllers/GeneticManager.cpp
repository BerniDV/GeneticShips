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

		//Los cruzo (de momento) haciendo que los dos mejores se reproduzca con todos los mejores
		//Metodo de la ruleta (seleccion de montecarlo): Calcular la aptitud relativa al grupo y usarla como probabilidad, se tira la ruleta y se escoge como padre la region en la que cae.
		for (int i = 0; i < aptitudes.Num(); i++)
		{

			float rulete = FMath::FRandRange(0.f, 1.f);

			DNAParents.Add(actualGenerationDNA[GetIndexChromosomeRulete(aptitudes, rulete)]);

		}

		for (int j = 0; j < DNAParents.Num() - 1; ++j)
		{
			AChromosome* son = CrossOver(DNAParents[j], DNAParents[j + 1]);

			DNAResult.Add(son);
		}

		DNAResult.Add(CrossOver(DNAParents[0], DNAParents[DNAParents.Num() - 1]));

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

	float probabilityCrossOver = (rand() % 100) + 1;

	AChromosome* son; //= GetWorld()->SpawnActor<AChromosome>();

	//Aqui aplicare diferentes metodos de crossover como de doble punto etc...

	if(probabilityCrossOver < 60)
	{
		
		son = parent1->Clone();

	}else
	{

		son = parent2->Clone();
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


	return individual->GetGene(Gene::timeAlive) + individual->GetGene(Gene::damageCaused);
}

void AGeneticManager::SetPopulationSize(int population)
{

	populationSize = population;
}

int AGeneticManager::GetIndexChromosomeRulete(TArray<float> aptitudes, float rulete)
{

	int index;

	float amountProbabilities = 0.f;

	for (int i = 0; i < aptitudes.Num(); i++)
	{

		amountProbabilities += aptitudes[i];

		if (amountProbabilities >= rulete)
		{

			index = i;
			break;
		}
	}

	return index;
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

