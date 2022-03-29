// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "EnemyActionPawn.generated.h"

class UBoxComponent;
class AChromosome;
class ABasicProjectile;
class UenemyMovementComponent;
class URotationComponent;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AEnemyActionPawn : public AActionPawn
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyDead);
	FOnEnemyDead signalOnEnemyDead;

	AEnemyActionPawn();

	void SetID(int32 newEnemyID);
	int32 GetID();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	void InitMovementCompnent(float _speedDropRate, float _defaultMaxAcceleration, float _defaultMaxSpeed, float _maxAcceleration, float _maxSpeed, float _accelerationSpeed, float _decelerationSpeed, float _meneuverabilityInPercent);

	void SetRandomGenes();

	void ApplyFenotipe();
	void ApplyMovementGenes();

	void SetChromosome(AChromosome* newChromosome);
	AChromosome* GetChromosome();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void PlayDeath() override;

	void SetPosition(FVector newPosition);

	UFUNCTION(NetMulticast, Reliable)
	void SpawnParticlesDeath();

	UFUNCTION()
	void EnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Fire(FVector locationToFire, FVector target);

	void MoverForward(float movement);

	void MoverRight(float movement);

	virtual void ExecuteRotation(FRotator rotator) override;

	FVector GetPredictedPosition();
	float GetInterpolationSpeed();

	void OnEnemyDead();

protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void Destroyed() override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBoxComponent* boxComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* meshComponent;

private:

	UPROPERTY(Replicated)
	int32 id;

	UPROPERTY(Replicated)
	AChromosome* enemyChromosome;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<UDamageType> damageType;

	//UPROPERTY(Replicated)
	//FVector position;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<ABasicProjectile> projectile;

	UPROPERTY(Replicated)
	UTranslationComponent* translationComponent;

	UPROPERTY(Replicated)
	URotationComponent* rotationComponent;

};
