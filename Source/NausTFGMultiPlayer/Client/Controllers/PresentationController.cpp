// Fill out your copyright notice in the Description page of Project Settings.


#include "PresentationController.h"

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

void UPresentationController::ShowNotLockingMouseCursor(UUserWidget* UIMenu)
{

	signalShowNotLockingCursor.Broadcast(UIMenu);
}

void UPresentationController::HideAndLockMouseCursor(UUserWidget* UIMenu)
{

	signalHideAndLockMouseCursor.Broadcast(UIMenu);
}

