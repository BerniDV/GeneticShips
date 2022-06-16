// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include <future>
#include "ActionGameMode.generated.h"

class AEnergyPickUp;
class AChromosome;
class AEnemyManager;
class AGeneticManager;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AActionGameMode();

	
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void BeginPlay() override;

	void SetTeam(APlayerController* PlayerController);

	UFUNCTION()
	void EndGame();

	UFUNCTION()
	TArray<AChromosome*> SetUpNextGeneration(TArray<AChromosome*> actualGeneration);


	UFUNCTION()
	void SetUpFirstGeneration();

	UFUNCTION()
	void InitializeNextRound();

	void DestroyGeneration(TArray<AChromosome*> &generation);

	UFUNCTION()
	void ProcesEndRound();

	UFUNCTION()
	void ProcesNewRound(TArray<AChromosome*>& newGeneration);

	void ProcesBetweenRounds(TArray<AChromosome*> actualGenerationresult);

	void SetRound(int round);

	void SetPopulationSize(int populationSize);

	UFUNCTION()
	void SpawnPickUp();

	void UpdateEventTimerGameState(int timeInSeconds);

protected:

	virtual void Tick(float DeltaSeconds) override;

private:

	TMap<int32, APlayerController*> playersInGame;

	const uint32 maxplayers = 2;

	FTimerHandle timerHandler;
	const int startWait = 10;
	const int betweenRoundsWait = 5;
	const int roundTime = 50;

	AGeneticManager* geneticManager;
	AEnemyManager* enemyManager;

	std::future<TArray<AChromosome*>> roundResultFuture;

	TSubclassOf<AEnergyPickUp> pilotPickUpClass;

	UPROPERTY()
	AEnergyPickUp* pilotPickUpEnergy;

	FVector teamPosition;

};
