// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"

UCustomGameInstance::UCustomGameInstance()
{


}

void UCustomGameInstance::SetLocalPlayerController(APlayerController* localController)
{

	localPlayerController = localController;
}

APlayerController* UCustomGameInstance::GetLocalPlayerController()
{

	return localPlayerController;
}
