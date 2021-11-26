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
	void SetReady(bool ready);

	UFUNCTION(Client, Reliable)
	void UpdateNumPlayers(int32 numPlayers);

	virtual void ClientTravelInternal_Implementation(const FString& URL, ETravelType TravelType, bool bSeamless, FGuid MapPackageGuid) override;

	void SetId(int32 Id);

	int32 GetId();


protected:

	virtual void BeginPlay() override;

private:

	int32 Id;

};
