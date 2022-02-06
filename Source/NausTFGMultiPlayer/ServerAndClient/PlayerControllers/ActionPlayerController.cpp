// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "ArtilleryActionPlayerController.h"
#include "PilotActionPlayerController.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCamera.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCameraManager.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/ActionPlayerState.h"
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


void AActionPlayerController::Initialize(MatchOptions matchOptions)
{

	AActionPlayerState* playerState = GetPlayerState<AActionPlayerState>();

	playerState->SetTeamID(matchOptions.teamID);
	GetWorld()->GetGameState()->GetPlayerStateFromUniqueNetId(FUniqueNetIdWrapper());

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;


	switch (matchOptions.roleSelected)
	{

	case NausTFGRolTypes::ArtilleryActionRolType:

		playerControllerImpl = GetWorld()->SpawnActor<AArtilleryActionPlayerController>(spawnParameters);

		break;

	case NausTFGRolTypes::PilotActionRolType:

		playerControllerImpl = GetWorld()->SpawnActor<APilotActionPlayerController>(spawnParameters);

		break;
		
	default:
		break;
	}
	
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

		InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, playerControllerImpl, &AActionPlayerControllerImpl::StartShooting);
		InputComponent->BindAction("Fire", EInputEvent::IE_Released, playerControllerImpl, &AActionPlayerControllerImpl::StopShooting);

		InputComponent->BindAxis("BoostSpeedUp", playerControllerImpl, &AActionPlayerControllerImpl::BoostSpeed);
		//InputComponent->BindAxis("BoostSpeedDown",playerControllerImpl, &AActionPlayerControllerImpl::BoostSpeed);

		InputComponent->BindAxis("CameraPitch", playerControllerImpl, &AActionPlayerControllerImpl::PitchCamera);
		InputComponent->BindAxis("CameraYaw", playerControllerImpl, &AActionPlayerControllerImpl::YawCamera);
	}
	
}

//Esta funcion es un callback del momento en el que el servidor replica al cliente playerControllerImpl
void AActionPlayerController::Client_InitializeClientPlayerControllerImpl_Implementation()
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

float AActionPlayerController::GetPlayerHealth()
{

	return GetPlayerState<AActionPlayerState>()->GetHealth();
}

void AActionPlayerController::SetPlayerHealth(float value)
{
	if (GetLocalRole() == ROLE_Authority)
		GetPlayerState<AActionPlayerState>()->SetHealth(value);
		
}

float AActionPlayerController::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{

	float currentHealth = GetPlayerHealth() - DamageAmount;
	SetPlayerHealth(currentHealth);
	return currentHealth;
}

int AActionPlayerController::GetTeamId()
{

	AActionPlayerState* myPlayerState = Cast<AActionPlayerState>(PlayerState);
	
	return myPlayerState->GetTeamID();
}

float AActionPlayerController::GetCadency()
{

	return playerControllerImpl->GetCadency();
}

float AActionPlayerController::GetTimeSinceLastProjectile()
{

	return playerControllerImpl->GetTimeSinceLastProjectile();
}


void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void AActionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}
