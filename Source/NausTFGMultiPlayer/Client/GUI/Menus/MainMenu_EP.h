// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenusDefaultBehaviours.h"
#include "MainMenu_EP.generated.h"


/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UMainMenu_EP : public UMenusDefaultBehaviours
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickPilotButton);
	FOnClickPilotButton signalOnClickPilotButton;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickArtilleryButton);
	FOnClickArtilleryButton signalOnClickArtilleryButton;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickImReady);
	FOnClickImReady signalOnClickImReady;

	UMainMenu_EP();

	UFUNCTION(BlueprintCallable, DisplayName = "OnCLickPilotButton")
	void OnClickPilotButton();

	UFUNCTION(BlueprintCallable, DisplayName = "OnCLickArtilleryButton")
	void OnClickArtilleryButton();

	UFUNCTION(BlueprintCallable, DisplayName = "OnCLickImReady")
	void OnClickImReady();

	void SetSelectionRolToPilot();

	void SetSelectionRolToArtillery();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Text")
	FString RolTypeSelectedText;
	
};
