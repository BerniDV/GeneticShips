// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerControllerImpl.h"
#include "ArtilleryActionPlayerController.generated.h"

class AActionPawn;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AArtilleryActionPlayerController : public AActionPlayerControllerImpl
{
	GENERATED_BODY()

public:

	AArtilleryActionPlayerController();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	virtual UClass* GetDefaultPawn() override;

	virtual AActionCamera* SpawnActionCamera() override;

	virtual void PitchCamera(float value) override;

	virtual void YawCamera(float value) override;

	void Fire();

	virtual void StartShooting() override;
	virtual void StopShooting() override;

	float GetCadency() override;
	float GetTimeSinceLastProjectile() override;


	virtual void CreaMenus() override;
	virtual void LoadHUD() override;
	virtual void BindSignals() override;

private:

	UClass* reference;

	float cadencyOfTheGunInSeconds;

	bool bIsShooting;
	float timeSinceLastProjectile;

	FVector2D cameraInput;
};
