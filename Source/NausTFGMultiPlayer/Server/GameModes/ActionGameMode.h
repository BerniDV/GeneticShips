// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ActionGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	AActionGameMode();

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

};
