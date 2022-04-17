// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionGameController.h"
#include "PilotActionGameController.generated.h"

class UPilotHUD_EP;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UPilotActionGameController : public UActionGameController
{
	GENERATED_BODY()

public:

	UPilotActionGameController();

	virtual void CreaMenus() override;

	virtual void LoadHUD() override;

	virtual void UnloadHUD() override;

	virtual void InitializeMenus() override;

	virtual void UpdateHealth(float health) override;


private:

	TSubclassOf<UPilotHUD_EP> PawnHUDClass;

	UPROPERTY()
	UPilotHUD_EP* pilotHUD;
	
};
