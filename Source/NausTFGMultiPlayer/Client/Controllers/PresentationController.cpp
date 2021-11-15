// Fill out your copyright notice in the Description page of Project Settings.


#include "PresentationController.h"

#include "Blueprint/UserWidget.h"

UPresentationController::UPresentationController()
{


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

void UPresentationController::HideAndLockMouseCursor(UUserWidget* UIMenu)
{

	signalHideAndLockMouseCursor.Broadcast(UIMenu);
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

