// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

class AChromosome;
class AEnemyActionPawn;
UCLASS()
class NAUSTFGMULTIPLAYER_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

	//Per repte utilitzar promises i futures per a que la mateixa funcio retorni els resultats
	void SpawnGeneration(TArray<AChromosome*> generationDNA);

	void DeleteAllEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	TSubclassOf<AEnemyActionPawn> enemyClass;

	int32 nextEnemyID;

	UPROPERTY()
	TMap<int32, AEnemyActionPawn*> EnemyMap;

};
