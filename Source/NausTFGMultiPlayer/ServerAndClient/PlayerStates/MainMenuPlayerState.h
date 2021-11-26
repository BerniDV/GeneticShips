// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainMenuPlayerState.generated.h"


enum class NausTFGRolTypes_Enum : uint8;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AMainMenuPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerReady);
	FOnPlayerReady signalOnPlayerReady;

	UFUNCTION(BlueprintCallable, DisplayName = "OnCLickPilotButton")
	void OnPlayerReady();

	AMainMenuPlayerState();


	UFUNCTION(Server, Reliable)
	void SetRolType(NausTFGRolTypes_Enum rolType);

	NausTFGRolTypes_Enum GetRolType();

	void SetIsReady(bool ready);

	bool GetIsReady();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	
private:

	UPROPERTY(Replicated)
	NausTFGRolTypes_Enum rolSelected;

	bool isReady;

};
