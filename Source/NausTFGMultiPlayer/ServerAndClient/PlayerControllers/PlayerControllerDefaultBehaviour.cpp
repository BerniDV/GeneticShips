// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerDefaultBehaviour.h"
#include "Blueprint/UserWidget.h"


void APlayerControllerDefaultBehaviour::InitializeMenus()
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

void APlayerControllerDefaultBehaviour::LoadMenu(UUserWidget* UIMenu)
{

	if (IsLocalPlayerController())
	{

		UIMenu->bIsFocusable = true;
		UIMenu->AddToViewport();
		
	}

}

void APlayerControllerDefaultBehaviour::UnloadMenu(UUserWidget* UIMenu)
{

	if (IsLocalPlayerController())
	{

		UIMenu->RemoveFromViewport();
		UIMenu->bIsFocusable = false;

	}

}

void APlayerControllerDefaultBehaviour::bindSignals()
{

}
