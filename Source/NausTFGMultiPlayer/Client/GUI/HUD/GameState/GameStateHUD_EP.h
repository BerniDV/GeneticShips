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
	FString GetRoundCountDownText();

	UFUNCTION(BlueprintCallable)
	int GetNumRound();

	UFUNCTION(BlueprintCallable)
	int GetRoundCountDownInSeconds();

	void SetRoundCountDownInSeconds(int _roundCountDownInSeconds);

	void SetEnemiesAlive(int enemies);

	void UpdateEnemiesAliveText();

	void UpdateRoundCountDownText();

	UFUNCTION(BlueprintCallable)
	FString GetEnemiesAliveText();

	UFUNCTION(BlueprintCallable)
	int GetEnemiesAlive();

protected:

	UPROPERTY(BlueprintReadWrite, Category = "gameStateInfo")
	FString numRoundText;

	UPROPERTY(EditAnywhere, Category = "gameStateInfo")
	int round;

	UPROPERTY(BlueprintReadWrite, Category = "gameStateInfo")
	FString enemiesAliveText;

	UPROPERTY(EditAnywhere, Category = "gameStateInfo")
	int enemiesAlive;

	UPROPERTY(BlueprintReadWrite, Category = "gameStateInfo")
	int roundCountDownInSeconds;

	UPROPERTY(BlueprintReadWrite, Category = "gameStateInfo")
	FString roundCountDownText;

private:

	
	
};
