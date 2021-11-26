// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPlayerController.h"
#include "PilotActionPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API APilotActionPlayerController : public AActionPlayerController
{
	GENERATED_BODY()

public:

	APilotActionPlayerController();


	virtual void BeginPlay() override;
	
};
