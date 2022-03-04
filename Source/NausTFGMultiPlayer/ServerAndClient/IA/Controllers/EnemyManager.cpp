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

std::future<TArray<AChromosome*>> AEnemyManager::SpawnGeneration(TArray<AChromosome*> generationDNA)
{

	DeleteAllEnemies();

	roundResultPromise = std::promise<TArray<AChromosome*>>();

	for(int i = 0; i < generationDNA.Num(); i++)
	{

		FVector spawnLocation(FMath::RandRange(-5000.f, 5000.f), FMath::RandRange(-5000.f, 5000.f), FMath::RandRange(-5000.f, 5000.f));

		AActor* spawnedActor = nullptr;
		spawnedActor = GetWorld()->SpawnActor<AActionPawn>(enemyClass, spawnLocation, FRotator::ZeroRotator);
		AAIBaseController* controller = GetWorld()->SpawnActor<AAIBaseController>();

		if (spawnedActor != nullptr)
		{

			//Esto sera un bucle por cada adn del array
			AEnemyActionPawn* Enemy = Cast<AEnemyActionPawn>(spawnedActor);
			controller->Possess(Enemy);

			Enemy->SetID(nextEnemyID);
			Enemy->SetReplicates(true);
			generationDNA[i]->SetOwner(Enemy);
			Enemy->SetChromosome(generationDNA[i]);
			

			EnemyMap.Add(nextEnemyID, Enemy);
			++nextEnemyID;

			//En caso de spawn incorrecto intentamos otra vez
		}else
		{

			i--;
		}
	}

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

		result.Add(x.Value->GetChromosome());
	}

	roundResultPromise.set_value(result);
}

