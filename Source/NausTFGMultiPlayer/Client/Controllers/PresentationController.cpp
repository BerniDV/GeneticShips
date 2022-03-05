// Fill out your copyright notice in the Description page of Project Settings.


#include "PresentationController.h"
#include "VisualEffectsController.h"
#include "Blueprint/UserWidget.h"

UPresentationController::UPresentationController()
{

	//visualEffectsController = NewObject<AVisualEffectsController>(this, TEXT("ParticleCtrl"));
	
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
	
	UIMenu->bIsFocusable = true;
	UIMenu->AddToViewport();
}

void UPresentationController::UnloadMenu(UUserWidget* UIMenu)
{

	UIMenu->RemoveFromViewport();
	UIMenu->bIsFocusable = false;
}

void UPresentationController::SpawnParticlesAtLocation(FVector Location, FVector Scale)
{
	
	visualEffectsController->SpawnParticlesAtLocation(Location, Scale);
}

void UPresentationController::SpawnFollowingParticles(USceneComponent* AttatchTo, FVector Scale)
{

	visualEffectsController->SpawnFollowingParticles(AttatchTo, Scale);
}

