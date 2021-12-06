// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerControllerImpl.h"
#include "PilotActionPlayerController.generated.h"

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

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	URotationComponent* rotationComponent;

private:

	UClass* reference;

	
	
};
