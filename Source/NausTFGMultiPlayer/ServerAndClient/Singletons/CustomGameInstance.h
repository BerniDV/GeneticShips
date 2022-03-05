// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"


enum class NausTFGRolTypes : uint8;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UCustomGameInstance();

	void SetLocalPlayerController(APlayerController* localController);

	APlayerController* GetLocalPlayerController();


private:

	APlayerController* localPlayerController;
};
