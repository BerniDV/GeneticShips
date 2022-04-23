// Fill out your copyright notice in the Description page of Project Settings.


#include "PresentationController.h"

#include "SoundsController.h"
#include "VisualEffectsController.h"
#include "Blueprint/UserWidget.h"

UPresentationController::UPresentationController()
{

	//visualEffectsController = NewObject<AVisualEffectsController>(this, TEXT("ParticleCtrl"));

	ConstructorHelpers::FClassFinder<ASoundsController> soundsController_BPClass(TEXT("/Game/Client/Sounds/SoundsController_BP"));
	soundsControllerClass = soundsController_BPClass.Class;
}

void UPresentationController::Init(APlayerController* owner)
{

	unimplemented();
}

void UPresentationController::InitializeMenus()
{

	unimplemented();
}

void UPresentationController::CreaMenus()
{

	unimplemented();
}

void UPresentationController::BindSignals()
{
	unimplemented();
}

void UPresentationController::ShowNotLockingMouseCursor(UUserWidget* UIMenu)
{

	signalShowNotLockingCursor.Broadcast(UIMenu);
}

void UPresentationController::HideAndLockMouseCursor()
{

	signalHideAndLockMouseCursor.Broadcast();
}

void UPresentationController::LoadMenu(UUserWidget* UIMenu)
{
	if(UIMenu)
	{

		UIMenu->bIsFocusable = true;
		UIMenu->AddToViewport();
	}
	
}

void UPresentationController::UnloadMenu(UUserWidget* UIMenu)
{

	if(UIMenu)
	{

		UIMenu->RemoveFromViewport();
		UIMenu->bIsFocusable = false;
	}
	
}

void UPresentationController::SpawnParticlesAtLocation(FVector Location, FVector Scale)
{
	
	visualEffectsController->SpawnParticlesAtLocation(Location, Scale);
}

void UPresentationController::SpawnFollowingParticles(USceneComponent* AttatchTo, FVector Scale)
{

	visualEffectsController->SpawnFollowingParticles(AttatchTo, Scale);
}

void UPresentationController::SpawnSoundAtLocation(FVector Location, Sounds sound, float soundMultiplier)
{

	soundsController->SpawnSoundAtLocation(Location, sound, FRotator::ZeroRotator, soundMultiplier);
}

