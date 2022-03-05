// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VisualEffectsController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NAUSTFGMULTIPLAYER_API AVisualEffectsController : public AActor
{
	GENERATED_BODY()

public:

	AVisualEffectsController();

	void SpawnParticlesAtLocation(FVector Location, FVector Scale);

	void SpawnFollowingParticles(USceneComponent* AttatchTo, FVector Scale);


protected:

	UPROPERTY(EditAnywhere)
	class UParticleSystem* explosionEffect;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* fireEffect;
	
};
