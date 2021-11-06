// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerDefaultBehaviour.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class NAUSTFGMULTIPLAYER_API APlayerControllerDefaultBehaviour : public APlayerController
{
	GENERATED_BODY()


public:

	virtual void InitializeMenus();

	virtual void CreaMenus();

	virtual void ShowNotLockingMouseCursor(UUserWidget* UIMenu);

	virtual void HideAndLockMouseCursor(UUserWidget* UIMenu);

	virtual void LoadMenu(UUserWidget* UIMenu);

	virtual void UnloadMenu(UUserWidget* UIMenu);

	virtual void bindSignals();
};
