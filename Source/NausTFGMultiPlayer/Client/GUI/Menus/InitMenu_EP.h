// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenusDefaultBehaviours.h"
#include "InitMenu_EP.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UInitMenu_EP : public UMenusDefaultBehaviours
{
	GENERATED_BODY()


public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnClickAnyKey);
	FOnClickAnyKey signalOnClickAnyKey;

	UFUNCTION(BlueprintCallable, DisplayName = "OnCLickAnyButton")
	void OnClickAnyKey();


};
