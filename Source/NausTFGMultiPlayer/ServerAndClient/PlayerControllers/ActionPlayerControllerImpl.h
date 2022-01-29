// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "ActionPlayerControllerImpl.generated.h"

class AActionCamera;
class URotationComponent;
class UTranslationComponent;
class UPresentationController;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionPlayerControllerImpl : public AActor
{
	GENERATED_BODY()


public:

	AActionPlayerControllerImpl();

	 virtual void InitializePresentationController();

	 virtual void BindSignals();

	virtual UClass* GetDefaultPawn();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	UPresentationController* GetPresentationController();

	virtual void Rotate(float turnValue);

	virtual void MoveForward(float movement);

	virtual void MoveRight(float movement);

	virtual void ImpulseON();
	virtual void ImpulseOFF();

	virtual void DecelerationON();
	virtual void DecelerationOff();
	virtual void BoostSpeed(float value);

	virtual void PitchCamera(float value);
	virtual void YawCamera(float value);

	virtual AActionCamera* SpawnActionCamera();

	void SetCameraManager(APlayerCameraManager* _cameraManager);

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

protected:

	APlayerCameraManager* cameraManager;

private:

	UPresentationController* presentationController;

};
