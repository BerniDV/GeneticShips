// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ActionPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionPlayerState : public APlayerState
{
	GENERATED_BODY()


public:

	AActionPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	UFUNCTION()
	void OnHealthUpdate();

	float GetHealth();
	void SetHealth(float value);
	void AddHealth(float value);

	void SetTeamID(int value);
	int GetTeamID();

private:

	float maxHealth;

	UPROPERTY(ReplicatedUsing = OnHealthUpdate)
	float health;

	UPROPERTY(Replicated)
	int  teamID;
	
};
