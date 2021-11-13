// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "ActionPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionPlayerController : public APlayerControllerDefaultBehaviour
{
	GENERATED_BODY()

public:

	AActionPlayerController();

	virtual void InitializePresentationController() override;

	virtual void BindSignals() override;




private:


	
};
