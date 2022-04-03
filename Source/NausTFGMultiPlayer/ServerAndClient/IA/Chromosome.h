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

	FVector GetSizeGene();
	void SetSizeGene(FVector SizeGene);

	void ApplyFenotipe();

	void ApplyFenotipeSize(FVector size);

	void ApplyMovementGenes();

	void SetRandomGenes();

	void Mutation();

	AChromosome* Clone();

	void SetDamageCausedTopTarget(float amount);

	float GetDamageCausedToTarget();

	void AddDamageCausedToTarget(float amount);

	float GetTimeAlive();

	void SetTimeAlive(float time);

	float GetImpactDamage();
	void SetImpactDamage(float damage);

	float GetSpeedDropRate();
	void SetSpeedDropRate(float value);
	float GetDefaultMaxAcceleration();
	void SetDefaultMaxAcceleration(float value);
	float GetMaxAcceleration();
	void SetMaxAcceleration(float value);
	float GetDefaultMaxSpeed();
	void SetDefaultMaxSpeed(float value);
	float GetMaxSpeed();
	void SetMaxSpeed(float value);
	float GetAccelerationSpeed();
	void SetAccelerationSpeed(float value);
	float GetDecelerationSpeed();
	void SetDecelerationSpeed(float value);
	float GetManeuverabilityInPercent();
	void SetManeuverabilityInPercent(float value);

	float GetGene(Gene gene);
	void SetGene(Gene gene, float value);

	void SetbAlive(bool value);
	void SetGenesArray(TArray<float> genes);
	TArray<float> GetGenes();

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
	 */
	
	TArray<float> genesArray;

	bool bAlive;

	int numGenes = 13;

	USceneComponent* root;

};
