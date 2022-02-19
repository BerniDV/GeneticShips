// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ActionGameMode.generated.h"

class AGeneticManager;
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

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void BeginPlay() override;

	void SetTeam(APlayerController* PlayerController);

	UFUNCTION()
	void EndGame();

private:

	TMap<int32, APlayerController*> playersInGame;

	const uint32 maxplayers = 2;

	AGeneticManager* geneticManager;

};
