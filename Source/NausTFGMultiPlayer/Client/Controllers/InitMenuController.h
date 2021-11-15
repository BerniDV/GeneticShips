// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PresentationController.h"
#include "InitMenuController.generated.h"

class AInitMenuPlayerController;
class UInitMenu_EP;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UInitMenuController : public UPresentationController
{
	GENERATED_BODY()

public:

	UInitMenuController();

	virtual void InitializeMenus() override;

	virtual void Init(APlayerController* owner) override;

	virtual void CreaMenus() override;

	void LoadInitMenu();

	void UnloadInitMenu();

	void AnyKeyPressed();

	void BindAnyKeySignal();

private:

	AInitMenuPlayerController* initMenuPlayerController;

	//referencia a la classe blueprint de initMenu
	TSubclassOf<UInitMenu_EP> initMenuClass;

	//instancia de la clase initMenu
	UPROPERTY()
	UInitMenu_EP* initMenu;
	
};
