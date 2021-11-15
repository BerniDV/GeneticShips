// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PresentationController.generated.h"

class AInitMenuPlayerController;
/**
 * 
 */
UCLASS(Abstract)
class NAUSTFGMULTIPLAYER_API UPresentationController : public UObject
{
	GENERATED_BODY()

public:


	UPresentationController();

	virtual void Init(APlayerController* owner);

	virtual void InitializeMenus();

	virtual void CreaMenus();

	virtual void BindSignals();

	virtual void ShowNotLockingMouseCursor(UUserWidget* UIMenu);

	virtual void HideAndLockMouseCursor(UUserWidget* UIMenu);

	virtual void LoadMenu(UUserWidget* UIMenu);

	virtual void UnloadMenu(UUserWidget* UIMenu);

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShowNotLockingCursor, UUserWidget*, userWidget);
	FShowNotLockingCursor signalShowNotLockingCursor;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHideAndLockMouseCursor, UUserWidget*, userWidget);
	FHideAndLockMouseCursor signalHideAndLockMouseCursor;

private:

	
};
