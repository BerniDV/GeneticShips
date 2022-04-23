// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerDefaultBehaviour.generated.h"

enum class Sounds : uint8;
class UPresentationController;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API APlayerControllerDefaultBehaviour : public APlayerController
{
	GENERATED_BODY()


public:

	APlayerControllerDefaultBehaviour();

	virtual void InitializePresentationController();

	virtual void CreaMenus();

	UFUNCTION(Client, Reliable)
	virtual void ShowNotLockingMouseCursor(UUserWidget* UIMenu);

	UFUNCTION(Client, Reliable)
	virtual void HideAndLockMouseCursor();
	
	virtual void BindSignals();

	ACameraActor* GetCameraActor();

	void SetCameraActor(ACameraActor* camera);

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	void SpawnSoundAtLocation(FVector Location, Sounds sound, float soundMultiplier);

protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY()
	UPresentationController* presentationController;


private:

	ACameraActor* cameraActor;
};
