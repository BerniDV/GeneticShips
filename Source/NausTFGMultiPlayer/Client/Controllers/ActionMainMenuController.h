// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PresentationController.h"
#include "ActionMainMenuController.generated.h"

class AActionPlayerController;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UActionMainMenuController : public UPresentationController
{
	GENERATED_BODY()

public:

	UActionMainMenuController();

	virtual void InitializeMenus() override;

	virtual void Init(APlayerController* owner) override;

	virtual void CreaMenus() override;

	virtual void BindSignals() override;

private:

	AActionPlayerController* actionPlayerController;
	
};
