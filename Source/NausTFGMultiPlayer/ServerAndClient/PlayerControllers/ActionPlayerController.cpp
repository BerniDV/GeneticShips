// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "ArtilleryActionPlayerController.h"
#include "PilotActionPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCamera.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCameraManager.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "Net/UnrealNetwork.h"



AActionPlayerController::AActionPlayerController()
{
	
	bReplicates = true;

	PlayerCameraManagerClass = AActionCameraManager::StaticClass();
	bAutoManageActiveCameraTarget = false;
}


void AActionPlayerController::BindSignals()
{
	Super::BindSignals();

	playerControllerImpl->BindSignals();
}



UClass* AActionPlayerController::GetDefaultPawn()
{

	return playerControllerImpl->GetDefaultPawn();
}


void AActionPlayerController::Initialize(NausTFGRolTypes roleType)
{

	switch (roleType)
	{

	case NausTFGRolTypes::ArtilleryActionRolType:

		playerControllerImpl = GetWorld()->SpawnActor<AArtilleryActionPlayerController>();

		break;

	case NausTFGRolTypes::PilotActionRolType:

		playerControllerImpl = GetWorld()->SpawnActor<APilotActionPlayerController>();

		break;
		
	default:
		break;
	}

	
	playerControllerImpl->SetOwner(this);


}

void AActionPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(playerControllerImpl && IsLocalPlayerController())
	{
		
		//InputComponent->BindAxis("Turn", playerControllerImpl, &AActionPlayerControllerImpl::Rotate);
		InputComponent->BindAxis("MoveForward", playerControllerImpl, &AActionPlayerControllerImpl::MoveForward);
		InputComponent->BindAxis("MoveRight", playerControllerImpl, &AActionPlayerControllerImpl::MoveRight);

		InputComponent->BindAction("Acceleration", EInputEvent::IE_Pressed, playerControllerImpl, &AActionPlayerControllerImpl::ImpulseON);
		InputComponent->BindAction("Acceleration", EInputEvent::IE_Released, playerControllerImpl, &AActionPlayerControllerImpl::ImpulseOFF);

		InputComponent->BindAction("Deceleration", EInputEvent::IE_Pressed, playerControllerImpl, &AActionPlayerControllerImpl::DecelerationON);
		InputComponent->BindAction("Deceleration", EInputEvent::IE_Released, playerControllerImpl, &AActionPlayerControllerImpl::DecelerationOff);

		InputComponent->BindAxis("BoostSpeedUp", playerControllerImpl, &AActionPlayerControllerImpl::BoostSpeed);
		//InputComponent->BindAxis("BoostSpeedDown",playerControllerImpl, &AActionPlayerControllerImpl::BoostSpeed);

		InputComponent->BindAxis("CameraPitch", playerControllerImpl, &AActionPlayerControllerImpl::PitchCamera);
		InputComponent->BindAxis("CameraYaw", playerControllerImpl, &AActionPlayerControllerImpl::YawCamera);
	}
	
}

//Esta funcion es un callback del momento en el que el servidor replica al cliente playerControllerImpl
void AActionPlayerController::InitializeClientPlayerControllerImpl_Implementation()
{

	presentationController = playerControllerImpl->GetPresentationController();
	SetupInputComponent();
	CreaMenus();
	BindSignals();
	HideAndLockMouseCursor();
	playerControllerImpl->SetCameraManager(PlayerCameraManager);
	SpawnActionCamera();

}


void AActionPlayerController::SpawnActionCamera()
{

	AActionCamera* camera = playerControllerImpl->SpawnActionCamera();

	SetCameraActor(camera);

	PlayerCameraManager->SetViewTarget(camera);

}

void AActionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AActionPlayerController, playerControllerImpl, COND_OwnerOnly);
}


void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void AActionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}
