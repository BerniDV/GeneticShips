// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundsController.generated.h"

enum class Sounds : uint8;
UCLASS()
class NAUSTFGMULTIPLAYER_API ASoundsController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundsController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnSoundAtLocation(FVector Location, Sounds sound, FRotator Rotation = FRotator::ZeroRotator, float VolumeMultiplier = 1);

protected:
	/*
	UPROPERTY(EditAnywhere)
	class USoundCue* explosionSound;

	UPROPERTY(EditAnywhere)
	class USoundCue* shootSound;
	*/
	UPROPERTY(EditAnywhere)
	class USoundCue* sounds[5];

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundAttenuation* shotAttenuation;

};
