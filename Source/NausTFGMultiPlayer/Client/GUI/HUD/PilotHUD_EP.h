// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDDefaultBehaviours.h"
#include "PilotHUD_EP.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UPilotHUD_EP : public UHUDDefaultBehaviours
{
	GENERATED_BODY()

public:

	UPilotHUD_EP();

	void SetLifeRendered(float life);

	UFUNCTION(BlueprintCallable)
	float GetLife();

private:

	UPROPERTY(EditAnywhere, Category = "PilotInfo")
	float renderedLifeInPercent;
	
};
