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

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	void SetRandomGenes();

	void ApplyFenotipe();

	void SetChromosome(AChromosome* newChromosome);
	AChromosome* GetChromosome();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;



	virtual void Destroyed() override;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBoxComponent* boxComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* meshComponent;

private:

	int32 id;

	UPROPERTY(Replicated)
	AChromosome* enemyChromosome;
	
};
