// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerControllerImpl.h"
#include "NausTFGMultiPlayer/Client/Controllers/InitMenuController.h"

#include "Net/UnrealNetwork.h"


AActionPlayerControllerImpl::AActionPlayerControllerImpl()
{

	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bOnlyRelevantToOwner = true;

}

void AActionPlayerControllerImpl::InitializePresentationController()
{
	
	if (!HasAuthority())
	{
		//Placeholder para no crash, se sustituye por inGameMenu
		presentationController = NewObject<UInitMenuController>();

		presentationController->Init(Cast<APlayerController>(GetOwner()));
	}

}

void AActionPlayerControllerImpl::BindSignals()
{
	
}

UClass* AActionPlayerControllerImpl::GetDefaultPawn()
{

	return nullptr;
}

void AActionPlayerControllerImpl::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

UPresentationController* AActionPlayerControllerImpl::GetPresentationController()
{

	return presentationController;
}

void AActionPlayerControllerImpl::Rotate(float turnValue)
{

}

void AActionPlayerControllerImpl::MoveForward(float movement)
{

}

void AActionPlayerControllerImpl::MoveRight(float movement)
{


}

void AActionPlayerControllerImpl::ImpulseON()
{


}

void AActionPlayerControllerImpl::ImpulseOFF()
{

}

void AActionPlayerControllerImpl::DecelerationON()
{

}

void AActionPlayerControllerImpl::DecelerationOff()
{

}

void AActionPlayerControllerImpl::BoostSpeed(float value)
{


}

void AActionPlayerControllerImpl::PitchCamera(float value)
{


}

void AActionPlayerControllerImpl::YawCamera(float value)
{


}

AActionCamera* AActionPlayerControllerImpl::SpawnActionCamera()
{

	return nullptr;
}

void AActionPlayerControllerImpl::SetCameraManager(APlayerCameraManager* _cameraManager)
{

	cameraManager = _cameraManager;
}


void AActionPlayerControllerImpl::BeginPlay()
{
	Super::BeginPlay();

	InitializePresentationController();
	
}

void AActionPlayerControllerImpl::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}


