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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNumEnemiesChanged);
	FOnNumEnemiesChanged signalEnemiesAlive;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewTimer);
	FOnNewTimer signalTimer;

	AActionGameState();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	UFUNCTION()
	void PlayerDead();

	UFUNCTION()
	void SetRound(int newRound);

	UFUNCTION(NetMulticast, Reliable)
	void ClientUpdateRound();

	UFUNCTION(NetMulticast, Reliable)
	void ClientUpdateEnemies();

	UFUNCTION(NetMulticast, Reliable)
	void ClientUpdateTimeUntilNextEvent();

	UFUNCTION(BlueprintCallable)
	int GetRound();

	UFUNCTION(BlueprintCallable)
	int GetEnemiesAlive();

	UFUNCTION()
	void SetEnemiesAlive(int numEnemies);

	UFUNCTION()
	void SetTimeUntilNextEvent(int timeInSeconds);

	UFUNCTION()
	int GetTimeUntilNextEvent();

	virtual void Tick(float DeltaSeconds) override;

private:

	UPROPERTY(ReplicatedUsing = ClientUpdateRound)
	int round;

	UPROPERTY(ReplicatedUsing = ClientUpdateEnemies)
	int enemiesAlive;

	//creo que lo que hare sera, a parte de enviar el tiempo en segundos en el momento en que cambie, hacer en el cliente un signal de cuando estè que queden 3 seg para hacer la cuenta atras en grande
	UPROPERTY(ReplicatedUsing = ClientUpdateTimeUntilNextEvent)
	int timeUntilNextEvent;

	float countSeconds;
};
