// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerControllerImpl.h"
#include "ArtilleryActionPlayerController.generated.h"

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

public:

	virtual UClass* GetDefaultPawn() override;

	virtual AActionCamera* SpawnActionCamera() override;

	virtual void PitchCamera(float value) override;

	virtual void YawCamera(float value) override;

	virtual void Fire() override;

private:

	UClass* reference;
};
