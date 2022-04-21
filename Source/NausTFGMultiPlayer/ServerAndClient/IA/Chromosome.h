// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "Chromosome.generated.h"

UCLASS()
class NAUSTFGMULTIPLAYER_API AChromosome : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChromosome();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	virtual void Destroyed() override;

	void ApplyFenotipe();

	
	void ApplyFenotipeSize(FVector size);
	void ApplyFenotipeColor(FLinearColor color);

	void ApplyMovementGenes();
	void ApplyHealthGenes();

	void SetRandomGenes();

	void Mutation();

	AChromosome* Clone();


	void SetGene(Gene typeGene, float value);
	void SetGene(int indexGene, float value);
	float GetGene(Gene typeGene);
	float GetGene(int indexGene);
	void AddToGene(Gene typeGene, float amount);

	void SetGenesArray(TArray<float> genes);

	int GetNumGenes();

private:


	/*
	 * 0: size
	 * 1: timeAlive
	 * 2: damageCaused
	 * 3: impactDamage
	 * 4: speedDropRate
	 * 5: defaultMaxAcceleration
	 * 6: maxAcceleration
	 * 7: defaultMaxSpeed
	 * 8: maxSpeed
	 * 9: accelerationSpeed
	 * 10: decelerationSpeed
	 * 11: maneuverabilityInPercent
	 * 12: fireCadancy
	 * 13 - 15: color
	 * 16: health
	 * 17: bulletDamage
	 * 18: traveledDistance
	 */
	
	TArray<float> genesArray;

	bool bAlive;

	int numGenes = 19;

	USceneComponent* root;

	const int maxSize = 100;
	const int maxImpactDamage = 100;
	const int maxSpeedDropRate = 10000;
	const int maxDefaultMaxAcceleration = 20000;
	const int maxMaxAcceleration = 20000;
	const int maxdefaultMaxSpeed = 4000;
	const int maxMaxSpeed = 4000;
	const int maxAccelerationSpeed = 4000;
	const int maxDecelerationSpeed = 4000;
	const int maxManeuverabilityInPercent = 100;
	const int maxFireCadancy = 20;
	const int maxHealth = 1000;
	const int maxBulletDamage = 100;


};
