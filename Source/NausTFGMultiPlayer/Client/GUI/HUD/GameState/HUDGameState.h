// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDGameState.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UHUDGameState : public UUserWidget
{
	GENERATED_BODY()

public:


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
	
};
