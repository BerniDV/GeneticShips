// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerControllerImpl.h"
#include "PilotActionPlayerController.generated.h"

class UTranslationComponent;
class URotationComponent;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API APilotActionPlayerController : public AActionPlayerControllerImpl
{
	GENERATED_BODY()

public:

	APilotActionPlayerController();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

public:

	virtual UClass* GetDefaultPawn() override;

	virtual void Rotate(float turnValue) override;

	void MoveForward(float movement) override;

	void MoveRight(float movement) override;

	virtual void ImpulseON() override;

	virtual void ImpulseOFF() override;

	virtual void DecelerationON() override;
	virtual void DecelerationOff() override;

	virtual void BoostSpeed(float value) override;


protected:

	

private:

	UClass* reference;
	
};



