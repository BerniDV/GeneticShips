// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneticManager.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"

// Sets default values
AGeneticManager::AGeneticManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	bAlwaysRelevant = true;

	ConstructorHelpers::FClassFinder <AEnemyActionPawn> refEnemyActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/EnemyActionPawn_BP"));
	enemyClass = refEnemyActionPawnBP.Class;

	nextEnemyID = 0;
}

// Called when the game starts or when spawned
void AGeneticManager::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
		GetWorld()->GetTimerManager().SetTimer(timerHandler, this, &AGeneticManager::SpawnEnemy, 0.1f, true);
	
}

// Called every frame
void AGeneticManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(EnemyMap.Num() == 300)
	{
		
		for(auto x: EnemyMap)
		{

			x.Value->Destroy();
		}

		for (auto It = EnemyMap.CreateConstIterator(); It; ++It)
		{

			EnemyMap.Remove(It.Key());

		}
	}

}

void AGeneticManager::SpawnEnemy()
{

	FVector spawnLocation(FMath::RandRange(-5000.f, 5000.f), FMath::RandRange(-5000.f, 5000.f), FMath::RandRange(-5000.f, 5000.f));
	
	AActor* spawnedActor = nullptr;
	spawnedActor = GetWorld()->SpawnActor<AActionPawn>(enemyClass, spawnLocation, FRotator::ZeroRotator);

	if(spawnedActor != nullptr)
	{

		AEnemyActionPawn* Enemy = Cast<AEnemyActionPawn>(spawnedActor);
		Enemy->SetID(nextEnemyID);
		++nextEnemyID;

		EnemyMap.Add(nextEnemyID, Enemy);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "EnemySpawned At: " + spawnLocation.ToString());

	}

}

