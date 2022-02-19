// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "EnemyActionPawn.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AEnemyActionPawn : public AActionPawn
{
	GENERATED_BODY()

public:

	AEnemyActionPawn();

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UBoxComponent* boxComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UStaticMeshComponent* meshComponent;
	
};
