// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerControllerImpl.h"

#include "ActionPlayerController.h"
#include "NausTFGMultiPlayer/Client/Controllers/InitMenuController.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerStates/ActionPlayerState.h"

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

	DOREPLIFETIME_CONDITION(AActionPlayerControllerImpl, teamMate, COND_InitialOnly);
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

void AActionPlayerControllerImpl::StartShooting()
{


}

void AActionPlayerControllerImpl::StopShooting()
{


}

float AActionPlayerControllerImpl::GetCadency()
{
	return TNumericLimits<float>::Max();
}

float AActionPlayerControllerImpl::GetTimeSinceLastProjectile()
{

	return 0;
}

void AActionPlayerControllerImpl::SetTeamMate(AActionPawn* _teamMate)
{

	teamMate = _teamMate;

}

AActionPawn* AActionPlayerControllerImpl::GetTeamMate()
{

	return teamMate;
}

void AActionPlayerControllerImpl::Client_HideTeamMateActor_Implementation()
{

	if (!HasAuthority() && teamMate)
	{

		teamMate->SetActorHiddenInGame(true);
		
	}
}


void AActionPlayerControllerImpl::BeginPlay()
{
	Super::BeginPlay();

	InitializePresentationController();

	
	
}

void AActionPlayerControllerImpl::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(teamMate)
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, teamMate->GetActorLocation().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("%d"), teamMate->HasPredictedMovement()));
	}

}


