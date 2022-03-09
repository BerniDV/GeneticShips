// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "NausTFGMultiPlayer/Client/GUI/HUD/HUDDefaultBehaviours.h"
#include "GameStateHUD_EP.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UGameStateHUD_EP : public UHUDDefaultBehaviours
{
	GENERATED_BODY()

public:

	UGameStateHUD_EP();

	void SetNumRound(int numRound);

	void UpdateNumRoundText();

	UFUNCTION(BlueprintCallable)
	FString GetNumRoundText();

	UFUNCTION(BlueprintCallable)
	int GetNumRound();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "numRoundInfo")
	FString numRoundText;

	UPROPERTY(EditAnywhere, Category = "numRoundInfo")
	int round;

private:

	
	
};
