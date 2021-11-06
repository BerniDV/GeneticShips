// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "InitMenuPlayerController.generated.h"

class UInitMenu_EP;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AInitMenuPlayerController : public APlayerControllerDefaultBehaviour
{
	GENERATED_BODY()


public:

	AInitMenuPlayerController();

	virtual void InitializeMenus() override;

	virtual void CreaMenus() override;

	void AnyKeyPressed();

	UFUNCTION()
	void JoinServerRoom();

	virtual void bindSignals() override;

protected:

	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:

	//referencia a la classe blueprint de initMenu
	TSubclassOf<UInitMenu_EP> initMenuClass;

	//instancia de la clase initMenu
	UPROPERTY()
	UInitMenu_EP* initMenu;
	
};
