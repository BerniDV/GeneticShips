// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "InitMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AInitMenuPlayerController : public APlayerControllerDefaultBehaviour
{
	GENERATED_BODY()


public:

	AInitMenuPlayerController();

	virtual void InitializePresentationController() override;

	virtual void CreaMenus() override;

	void AnyKeyPressed();

	UFUNCTION()
	void JoinServerRoom();

	virtual void bindSignals() override;

	void LoadInitMenu();

	void UnloadInitMenu();

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
};
