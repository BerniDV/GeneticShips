// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPlayerController.h"
#include "ArtilleryActionPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AArtilleryActionPlayerController : public AActionPlayerController
{
	GENERATED_BODY()

public:

	AArtilleryActionPlayerController();

	virtual void BeginPlay() override;
};
