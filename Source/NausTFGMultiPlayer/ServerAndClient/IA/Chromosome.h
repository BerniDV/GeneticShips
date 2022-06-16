// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

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

	void ApplyFenotipe(const std::vector<float> averageGenes);

	
	void ApplyFenotipeSize(FVector size);
	void ApplyFenotipeColor(const std::vector<float> averageGenes);

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

	 int maxSize = 100;
	 int maxImpactDamage = 25;
	 int maxSpeedDropRate = 10000;
	 int maxDefaultMaxAcceleration = 20000;
	 int maxMaxAcceleration = 20000;
	 int maxdefaultMaxSpeed = 7000;
	 int maxMaxSpeed = 7000;
	 int maxAccelerationSpeed = 7000;
	 int maxDecelerationSpeed = 7000;
	 int maxManeuverabilityInPercent = 70;
	 int maxFireCadancy = 30;
	 int maxHealth = 500;
	 int maxBulletDamage = 25;


};
