// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "ArtilleryActionPawn.generated.h"


class ABasicProjectile;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AArtilleryActionPawn : public AActionPawn
{
	GENERATED_BODY()

public:

	AArtilleryActionPawn();

	virtual void Fire() override;
	virtual void StopFire() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Fire();

	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;

protected:

	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<ABasicProjectile> projectile;

};
