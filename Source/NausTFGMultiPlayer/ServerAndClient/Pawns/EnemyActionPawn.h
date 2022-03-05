// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "EnemyActionPawn.generated.h"

class UBoxComponent;
class AChromosome;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AEnemyActionPawn : public AActionPawn
{
	GENERATED_BODY()

public:

	AEnemyActionPawn();

	void SetID(int32 newEnemyID);
	int32 GetID();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	void SetRandomGenes();

	void ApplyFenotipe();

	void SetChromosome(AChromosome* newChromosome);
	AChromosome* GetChromosome();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void PlayDeath() override;

	void SetPosition(FVector newPosition);

	UFUNCTION(NetMulticast, Reliable)
	void SpawnParticlesDeath();

	UFUNCTION()
	void EnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

	UPROPERTY(Replicated)
	FVector position;

};
