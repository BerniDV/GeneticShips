// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "AIBaseController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	bAlwaysRelevant = true;

	ConstructorHelpers::FClassFinder <AEnemyActionPawn> refEnemyActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/EnemyActionPawn_BP"));
	enemyClass = refEnemyActionPawnBP.Class;

	nextEnemyID = 0;

}

void AEnemyManager::SpawnEnemies()
{

	DeleteAllEnemies();


	for(int i = 0; i < 100; i++)
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

			EnemyMap.Add(nextEnemyID, Enemy);
			++nextEnemyID;

			//Aqui introduciré el adn en los enemigos
			Enemy->SetRandomGenes();

			//Esto lo haré de forma interna en el enemigo al aplicar un adn
			Enemy->ApplyFenotipe();

		}
	}
}

void AEnemyManager::DeleteAllEnemies()
{

	if(HasAuthority())
	{

		for (auto x : EnemyMap)
		{
			x.Value->GetController()->Destroy();
			x.Value->Destroy();
		}

		for (auto It = EnemyMap.CreateConstIterator(); It; ++It)
		{

			EnemyMap.Remove(It.Key());

		}

	}
	
}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

