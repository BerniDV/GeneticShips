// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerDefaultBehaviour.h"
#include "Blueprint/UserWidget.h"
#include "NausTFGMultiPlayer/Client/Controllers/PresentationController.h"


void APlayerControllerDefaultBehaviour::InitializePresentationController()
{

	unimplemented();
}

void APlayerControllerDefaultBehaviour::CreaMenus()
{

	unimplemented();
}

void APlayerControllerDefaultBehaviour::ShowNotLockingMouseCursor(UUserWidget* UIMenu)
{
	if(IsLocalPlayerController())
	{

		FInputModeUIOnly InputModeData;

		InputModeData.SetWidgetToFocus(UIMenu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		SetInputMode(InputModeData);
		SetShowMouseCursor(true);

	}

}

void APlayerControllerDefaultBehaviour::HideAndLockMouseCursor(UUserWidget* UIMenu)
{

	if(IsLocalPlayerController())
	{

		FInputModeGameOnly InputModeData;

		SetShowMouseCursor(false);
		SetInputMode(InputModeData);

	}
	
}


void APlayerControllerDefaultBehaviour::bindSignals()
{

	if(IsLocalPlayerController())
	{

		presentationController->signalShowNotLockingCursor.AddDynamic(this, &APlayerControllerDefaultBehaviour::ShowNotLockingMouseCursor);
		presentationController->signalHideAndLockMouseCursor.AddDynamic(this, &APlayerControllerDefaultBehaviour::HideAndLockMouseCursor);

	}
	

}


