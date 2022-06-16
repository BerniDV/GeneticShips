// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "AIBaseController.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = false;

	bAlwaysRelevant = true;

	ConstructorHelpers::FClassFinder <AEnemyActionPawn> refEnemyActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/EnemyActionPawn_BP"));
	enemyClass = refEnemyActionPawnBP.Class;

	nextEnemyID = 0;

}

std::future<TArray<AChromosome*>> AEnemyManager::SpawnGeneration(TArray<AChromosome*> generationDNA, FVector center)
{


	roundResultPromise = std::promise<TArray<AChromosome*>>();


	//Calcular media de todos los atributos de esta generacion
	std::vector<float> averageGenes(19, 0.f);

	for(int i = 0; i < averageGenes.size(); i++)
	{
		for (int j = 0; j < generationDNA.Num(); j++)
		{

			averageGenes[i] += generationDNA[j]->GetGene(i);
		}

		averageGenes[i] /= generationDNA.Num();

		UE_LOG(LogTemp, Warning, TEXT("Gen %d: %f"), i, averageGenes[i]);
	}


	for(int i = 0; i < generationDNA.Num(); i++)
	{

		FVector spawnLocation(FMath::RandRange(-300000.f + center.X, 300000.f + center.X), FMath::RandRange(-300000.f + center.Y, 300000.f + center.Y), FMath::RandRange(-300000.f+ center.Z, 300000.f + center.Z));

		AActor* spawnedActor = nullptr;
		spawnedActor = GetWorld()->SpawnActor<AActionPawn>(enemyClass, spawnLocation, FRotator::ZeroRotator);
		AAIBaseController* controller = GetWorld()->SpawnActor<AAIBaseController>();

		if (spawnedActor != nullptr)
		{

			//Esto sera un bucle por cada adn del array
			AEnemyActionPawn* Enemy = Cast<AEnemyActionPawn>(spawnedActor);

			Enemy->SetID(nextEnemyID);
			Enemy->SetReplicates(true);
			generationDNA[i]->SetOwner(Enemy);

			Enemy->SetChromosome(generationDNA[i], averageGenes);

			controller->Possess(Enemy);

			EnemyMap.Add(nextEnemyID, Enemy);
			++nextEnemyID;

			//En caso de spawn incorrecto intentamos otra vez
		}else
		{

			i--;
		}
	}

	int numeEnemies = EnemyMap.Num();
	GetWorld()->GetGameState<AActionGameState>()->SetEnemiesAlive(numeEnemies);

	return roundResultPromise.get_future();
}

void AEnemyManager::DeleteAllEnemies()
{

	if(HasAuthority() && EnemyMap.Num() > 0)
	{

		for (auto x : EnemyMap)
		{
			//x.Value->GetController()->Destroy();
			x.Value->Destroy();
		}

		for (auto It = EnemyMap.CreateConstIterator(); It; ++It)
		{

			EnemyMap.Remove(It.Key());

		}

		GetWorld()->GetGameState<AActionGameState>()->SetEnemiesAlive(0);

	}
	
}

void AEnemyManager::DeleteEnemy(int32 enemyID)
{

	if(EnemyMap.Find(enemyID) != nullptr)
	{
		if(EnemyMap[enemyID] != nullptr)
			EnemyMap[enemyID]->Destroy();
	}

	EnemyMap.Remove(enemyID);

	GetWorld()->GetGameState<AActionGameState>()->SetEnemiesAlive(EnemyMap.Num());
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	if(!HasAuthority())
	{

		roundResultPromise.set_value(TArray<AChromosome*>());
	}

	if(HasAuthority())
	{
		AGameStateBase* gameState = GetWorld()->GetGameState();
		Cast<AActionGameState>(gameState)->signalNewRound.AddDynamic(this, &AEnemyManager::CalculateResults);
	}
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AEnemyManager::Destroyed()
{

	Super::Destroyed();
}

void AEnemyManager::CalculateResults()
{

	TArray<AChromosome*> result;

	for (auto x : EnemyMap)
	{

		result.Add(x.Value->GetChromosome()->Clone());
	}

	DeleteAllEnemies();

	roundResultPromise.set_value(result);
}

