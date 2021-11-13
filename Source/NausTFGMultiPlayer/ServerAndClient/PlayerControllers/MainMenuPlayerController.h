// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "MainMenuPlayerController.generated.h"

enum class NausTFGRolTypes_Enum : uint8;
class AMainMenuCameraActor;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AMainMenuPlayerController : public APlayerControllerDefaultBehaviour
{
	GENERATED_BODY()


public:

	AMainMenuPlayerController();

	virtual void InitializePresentationController() override;

	virtual void BindSignals() override;

	void LoadMainMenu();

	void UnloadMainMenu();

	void SpawnMainMenuCamera();

	UFUNCTION()
	void SetRoleToPilot();

	UFUNCTION()
	void SetRoleToArtillery();

	UFUNCTION(Server, Reliable)
	void JoinGame();
	void JoinGame_Implementation();


protected:

	virtual void BeginPlay() override;

private:
	NausTFGRolTypes_Enum roleSelected;

};
