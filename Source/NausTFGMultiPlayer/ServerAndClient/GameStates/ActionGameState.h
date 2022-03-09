// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ActionGameState.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionGameState : public AGameState
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDead);
	FOnPlayerDead signalPlayerDead;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewRound);
	FOnNewRound signalNewRound;

	AActionGameState();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	UFUNCTION()
	void PlayerDead();

	UFUNCTION()
	void SetRound(int newRound);

	UFUNCTION(NetMulticast, Reliable)
	void ClientUpdateRound();

	UFUNCTION(BlueprintCallable)
	int GetRound();

private:

	UPROPERTY(ReplicatedUsing = ClientUpdateRound)
	int round;


};
