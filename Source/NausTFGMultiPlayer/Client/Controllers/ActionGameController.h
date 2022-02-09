// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PresentationController.h"
#include "ActionGameController.generated.h"

class UArtilleryHUD_EP;
class AActionPlayerController;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UActionGameController : public UPresentationController
{
	GENERATED_BODY()

public:

	UActionGameController();

	virtual void InitializeMenus() override;

	virtual void Init(APlayerController* owner) override;

	virtual void CreaMenus() override;

	virtual void BindSignals() override;

	void LoadHUD();
	void UnloadHUD();

private:

	//referencia a la classe blueprint de initMenu
	TSubclassOf<UArtilleryHUD_EP> HUDClass;

	AActionPlayerController* actionPlayerController;

	UPROPERTY()
	UArtilleryHUD_EP* artilleryHUD;

};
