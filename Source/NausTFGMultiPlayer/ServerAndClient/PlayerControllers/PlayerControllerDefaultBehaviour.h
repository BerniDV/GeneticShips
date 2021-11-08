// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerDefaultBehaviour.generated.h"

class UPresentationController;
/**
 * 
 */
UCLASS(Abstract)
class NAUSTFGMULTIPLAYER_API APlayerControllerDefaultBehaviour : public APlayerController
{
	GENERATED_BODY()


public:

	virtual void InitializePresentationController();

	virtual void CreaMenus();

	UFUNCTION()
	virtual void ShowNotLockingMouseCursor(UUserWidget* UIMenu);

	UFUNCTION()
	virtual void HideAndLockMouseCursor(UUserWidget* UIMenu);

	virtual void bindSignals();

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	UPresentationController* presentationController;
};
