// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerDefaultBehaviour.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameUserSettings.h"
#include "NausTFGMultiPlayer/Client/Controllers/PresentationController.h"
#include "Net/UnrealNetwork.h"


APlayerControllerDefaultBehaviour::APlayerControllerDefaultBehaviour()
{

	bReplicates = true;
}

void APlayerControllerDefaultBehaviour::InitializePresentationController()
{

	
}

void APlayerControllerDefaultBehaviour::CreaMenus()
{

	if (IsLocalPlayerController() && presentationController)
	{
		presentationController->CreaMenus();

	}
}

void APlayerControllerDefaultBehaviour::ShowNotLockingMouseCursor_Implementation(UUserWidget* UIMenu)
{
	if (IsLocalPlayerController())
	{

		FInputModeUIOnly InputModeData;

		InputModeData.SetWidgetToFocus(UIMenu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		SetInputMode(InputModeData);
		SetShowMouseCursor(true);

	}

}


void APlayerControllerDefaultBehaviour::HideAndLockMouseCursor_Implementation()
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

void APlayerControllerDefaultBehaviour::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& MovieSceneBlendses) const
{
	Super::GetLifetimeReplicatedProps(MovieSceneBlendses);
	
}

void APlayerControllerDefaultBehaviour::BeginPlay()
{
	Super::BeginPlay();

	//Pantalla modo window
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
	UserSettings->SetFullscreenMode(EWindowMode::Windowed);
	UserSettings->SetScreenResolution(FIntPoint(960, 540));
	UserSettings->ApplySettings(false);

	//CreaMenus();
	//BindSignals();


}


