// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainMenuGameMode.generated.h"

class AMainMenuPlayerController;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()


public:

	AMainMenuGameMode();

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	void UpdateNumPlayers(int32 numPlayers);
	

private:

	TArray<AMainMenuPlayerController*> PlayerControllerArray;
};
