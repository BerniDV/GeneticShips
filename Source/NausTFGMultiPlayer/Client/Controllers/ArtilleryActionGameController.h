// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionGameController.h"
#include "ArtilleryActionGameController.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UArtilleryActionGameController : public UActionGameController
{
	GENERATED_BODY()

public:

	UArtilleryActionGameController();

	virtual void CreaMenus() override;

	virtual void LoadHUD() override;

	virtual void UnloadHUD() override;

	virtual void InitializeMenus() override;


private:

	TSubclassOf<UArtilleryHUD_EP> PawnHUDClass;

	UPROPERTY()
	UArtilleryHUD_EP* artilleryHUD;
	
};
