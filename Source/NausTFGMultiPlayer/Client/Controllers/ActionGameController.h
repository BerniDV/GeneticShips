// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PresentationController.h"
#include "ActionGameController.generated.h"

class UHUDGameState;
class UGameStateHUD_EP;
class UHUDDefaultBehaviours;
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

	virtual void LoadHUD();
	virtual void UnloadHUD();

	virtual void UpdateHealth(float health);

	void LoadGameStateHUD();
	void UnloadGameStateHUD();

	void SetRound(int round);
	FString GetRound();

	void SetEnemiesAlive(int enemies);
	FString GetEnemiesAliveText();

	virtual void SpawnParticlesAtLocation(FVector Location, FVector Scale) override;

protected:

	APlayerController* actionPlayerController;

private:

	//referencia a la classe blueprint de initMenu
	TSubclassOf<UGameStateHUD_EP> GameStateHUDClass;

	UPROPERTY()
	UGameStateHUD_EP* gameStateHUD;

};
