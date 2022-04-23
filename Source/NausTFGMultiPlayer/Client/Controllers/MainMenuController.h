// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PresentationController.h"
#include "MainMenuController.generated.h"

class AMainMenuPlayerController;
class UMainMenu_EP;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UMainMenuController : public UPresentationController
{
	GENERATED_BODY()

public:

	UMainMenuController();

	virtual void InitializeMenus() override;

	virtual void Init(APlayerController* owner) override;

	virtual void CreaMenus() override;

	virtual void BindSignals() override;

	void LoadMainMenu();

	void UnloadMainMenu();

	void SetRoleToPilot();

	void SetRoleToArtillery();

	void SetNumPLayers(int32 numPlayers);

	void UpdateNumPlayers();

	

private:

	void BindSetPilotAsRoleSelected();

	void BindSetArtilleryAsRoleSelected();

	void BindImReadyButton();

protected:

	

private:

	AMainMenuPlayerController* mainMenuPlayerController;

	//referencia a la classe blueprint de initMenu
	TSubclassOf<UMainMenu_EP> mainMenuClass;

	//instancia de la clase mainMenu
	UPROPERTY()
	UMainMenu_EP* mainMenu;

	int32 numPlayersDataForMainMenuText;
	
};
