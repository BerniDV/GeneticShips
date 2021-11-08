// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "MainMenuPlayerController.generated.h"

class AMainMenuCameraActor;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AMainMenuPlayerController : public APlayerControllerDefaultBehaviour
{
	GENERATED_BODY()


public:

	AMainMenuPlayerController();

protected:

	virtual void BeginPlay() override;

private:

	AMainMenuCameraActor* cameraActor;
	
};
