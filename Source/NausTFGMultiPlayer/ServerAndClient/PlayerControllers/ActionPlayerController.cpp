// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "ArtilleryActionPlayerController.h"
#include "PilotActionPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCamera.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCameraManager.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ArtilleryActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/ActionPlayerState.h"
#include "Net/UnrealNetwork.h"



AActionPlayerController::AActionPlayerController()
{
	
	bReplicates = true;

	PlayerCameraManagerClass = AActionCameraManager::StaticClass();
	bAutoManageActiveCameraTarget = false;

	ConstructorHelpers::FClassFinder <APilotActionPawn> refPilotActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/PilotActionPawn_BP"));
	pilotReference = refPilotActionPawnBP.Class;

	ConstructorHelpers::FClassFinder <AArtilleryActionPawn> refArtilleryActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/ArtilleryActionPawn_BP"));
	artilleryReference = refArtilleryActionPawnBP.Class;

	playerHealth = 100.f;
}


void AActionPlayerController::BindSignals()
{
	Super::BindSignals();
	
	playerControllerImpl->BindSignals();
}



UClass* AActionPlayerController::GetDefaultPawn()
{
	if(playerControllerImpl)
	{

		return playerControllerImpl->GetDefaultPawn();
	}else
	{
		//No me gusta pero hasta no encontrar otra solucion se queda así
		//Problema: El patron state requiere que se haga spawn del actor en UE4, si lo hago así puede ser que unreal intente ver qual es el pawn que queremos antes de que se termine de spawnear
		if(playerRole == NausTFGRolTypes::PilotActionRolType)
		{

			return pilotReference;

		}else
		{

			return artilleryReference;
		}
	}
	
}


void AActionPlayerController::Initialize(MatchOptions matchOptions)
{

	AActionPlayerState* playerState = GetPlayerState<AActionPlayerState>();

	playerState->SetTeamID(matchOptions.teamID);
	GetWorld()->GetGameState()->GetPlayerStateFromUniqueNetId(FUniqueNetIdWrapper());

	FActorSpawnParameters spawnParameters;
	spawnParameters.Instigator = GetInstigator();
	spawnParameters.Owner = this;

	playerRole = matchOptions.roleSelected;

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
	
	SetViewTarget(camera);
}

void AActionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AActionPlayerController, playerControllerImpl, COND_OwnerOnly);
	DOREPLIFETIME(AActionPlayerController, playerHealth);
}

float AActionPlayerController::GetPlayerHealth()
{
	
	return GetPlayerState<AActionPlayerState>()->GetHealth();
}

void AActionPlayerController::SetPlayerHealth_Implementation(float value)
{

	if (GetLocalRole() == ROLE_Authority)
		GetPlayerState<AActionPlayerState>()->SetHealth(value);

	playerHealth = value;
}

bool AActionPlayerController::SetPlayerHealth_Validate(float value)
{

	return true;
}


float AActionPlayerController::ApplyDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{


	//float currentHealt = GetPlayerHealth();
	float newHealth = playerHealth - DamageAmount;

	if(newHealth <= 0)
	{
		newHealth = 0.f;
		Cast<APilotActionPawn>(GetPawn())->PlayDeath();

		AActionPawn* teamMate = playerControllerImpl->GetTeamMate();

		if(teamMate)
			teamMate->PlayDeath();
	}

	SetPlayerHealth(newHealth);
	return newHealth;
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

AActionPlayerControllerImpl* AActionPlayerController::GetPlayerControllerImpl()
{

	return playerControllerImpl;
}

void AActionPlayerController::SetInputEnabled(bool enable)
{
	if(enable)
	{
		EnableInput(this);
	}else
	{
		DisableInput(this);
	}
	
}


void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerHealth(playerHealth);

}

void AActionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("%f"), playerHealth));
}
