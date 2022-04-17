// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "ArtilleryActionPlayerController.h"
#include "PilotActionPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCamera.h"
#include "NausTFGMultiPlayer/Client/Cameras/ActionCameraManager.h"
#include "NausTFGMultiPlayer/Client/Controllers/ActionGameController.h"
#include "NausTFGMultiPlayer/Client/Controllers/PresentationController.h"
#include "NausTFGMultiPlayer/Server/GameModes/ActionGameMode.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ArtilleryActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/ActionPlayerState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Singletons/CustomGameInstance.h"
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
	
	maxPlayerHealth = 100.f;
	playerHealth = maxPlayerHealth;
}


void AActionPlayerController::BindSignals()
{
	Super::BindSignals();

	if (!HasAuthority())
		Cast<AActionGameState>(GetWorld()->GetGameState())->signalNewRound.AddDynamic(this, &AActionPlayerController::UpdateRound);
	
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
		//Problema: El patron state requiere que se haga spawn del actor en UE4, si lo hago así puede ser que unreal intente ver qual es el pawn que queremos antes de que se termine de spawnear,
					//por lo tanto devuelvo las referencias del playerController original en vez de usar el Impl en caso que no este inicializado
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

	InitializePresentationController();
	SetupInputComponent();
	CreaMenus();
	BindSignals();
	HideAndLockMouseCursor();

	//Crear funciones propias que llamen a estas
	playerControllerImpl->LoadGameStateHUD();
	playerControllerImpl->LoadHUD();
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
	
	return playerHealth;
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



void AActionPlayerController::ApplyDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{


	//float currentHealt = GetPlayerHealth();
	float newHealth = playerHealth - DamageAmount;

	if (newHealth <= 0)
	{
		newHealth = 0.f;
		Cast<APilotActionPawn>(GetPawn())->PlayDeath();

		AActionPawn* teamMate = playerControllerImpl->GetTeamMate();

		if (teamMate)
			teamMate->PlayDeath();
	}

	SetPlayerHealth(newHealth);


}

bool AActionPlayerController::ApplyDamage_Validate(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{

	return true;
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

void AActionPlayerController::SpawnParticlesAtLocation(FVector Location, FVector Scale)
{

	if(presentationController)
		presentationController->SpawnParticlesAtLocation(Location, Scale);

}

void AActionPlayerController::SpawnFollowingParticles(USceneComponent* AttatchTo, FVector Scale)
{
	if (presentationController)
		presentationController->SpawnFollowingParticles(AttatchTo, Scale);
}

void AActionPlayerController::UpdateRound_Implementation()
{
	if(IsLocalPlayerController())
	{

		int round = Cast<AActionGameState>(GetWorld()->GetGameState())->GetRound();

		Cast<UActionGameController>(presentationController)->SetRound(round);

	}
}


void AActionPlayerController::InitializePresentationController()
{

	playerControllerImpl->InitializePresentationController();
	presentationController = playerControllerImpl->GetPresentationController();
}

void AActionPlayerController::SetNewRound(int round)
{

	SetRoundServer(round);
}

void AActionPlayerController::SetNumEnemies(int enemies)
{

	SetNumEnemiesServer(enemies);
}

void AActionPlayerController::SetNumEnemiesServer_Implementation(int enemies)
{

	if (HasAuthority())
	{

		AActionGameMode* gameMode = Cast<AActionGameMode>(GetWorld()->GetAuthGameMode());

		if (gameMode)
		{

			gameMode->SetPopulationSize(enemies);
		}
	}
}

bool AActionPlayerController::SetNumEnemiesServer_Validate(int enemies)
{

	return true;
}

void AActionPlayerController::SetRoundServer_Implementation(int round)
{
	if (HasAuthority())
	{

		AActionGameMode* gameMode = Cast<AActionGameMode>(GetWorld()->GetAuthGameMode());

		if (gameMode)
		{

			gameMode->SetRound(round);
		}
	}

}

bool AActionPlayerController::SetRoundServer_Validate(int round)
{

	return true;
}

void AActionPlayerController::UpdateClientHealth()
{

	playerControllerImpl->UpdateClientHealth(playerHealth);
}

float AActionPlayerController::GetPlayerMaxHealth()
{

	return maxPlayerHealth;
}

void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerHealth(playerHealth);

	if(!HasAuthority())
		Cast<UCustomGameInstance>(GetGameInstance())->SetLocalPlayerController(this);

}

void AActionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}
