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
}

// Called when the game starts or when spawned
void AGeneticManager::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
		GetWorld()->GetTimerManager().SetTimer(timerHandler, this, &AGeneticManager::SpawnEnemy, 5.f, true);
	
}

// Called every frame
void AGeneticManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeneticManager::SpawnEnemy()
{

	FVector spawnLocation(FMath::RandRange(-5000.f, 5000.f), FMath::RandRange(-5000.f, 5000.f), FMath::RandRange(-5000.f, 5000.f));
	
	GetWorld()->SpawnActor<AActionPawn>(enemyClass, spawnLocation, FRotator::ZeroRotator);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, "EnemySpawned At: " + spawnLocation.ToString());
}

