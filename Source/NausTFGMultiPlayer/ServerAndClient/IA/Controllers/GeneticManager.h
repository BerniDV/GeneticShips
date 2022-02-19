// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneticManager.generated.h"

class AEnemyActionPawn;
UCLASS()
class NAUSTFGMULTIPLAYER_API AGeneticManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneticManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnEnemy();

private:

	FTimerHandle timerHandler;

	TSubclassOf<AEnemyActionPawn> enemyClass;

	int32 nextEnemyID;

	UPROPERTY()
	TMap<int32, AEnemyActionPawn*> EnemyMap;

};




