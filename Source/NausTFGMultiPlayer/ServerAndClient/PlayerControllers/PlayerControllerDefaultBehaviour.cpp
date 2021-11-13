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

	if (IsLocalPlayerController() && presentationController)
	{
		presentationController->CreaMenus();

	}
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


void APlayerControllerDefaultBehaviour::BindSignals()
{

	if(IsLocalPlayerController())
	{

		presentationController->signalShowNotLockingCursor.AddDynamic(this, &APlayerControllerDefaultBehaviour::ShowNotLockingMouseCursor);
		presentationController->signalHideAndLockMouseCursor.AddDynamic(this, &APlayerControllerDefaultBehaviour::HideAndLockMouseCursor);

	}
	

}

ACameraActor* APlayerControllerDefaultBehaviour::GetCameraActor()
{

	return cameraActor;
}

void APlayerControllerDefaultBehaviour::SetCameraActor(ACameraActor* camera)
{

	cameraActor = camera;
}

void APlayerControllerDefaultBehaviour::BeginPlay()
{
	Super::BeginPlay();

	CreaMenus();
	BindSignals();


}


