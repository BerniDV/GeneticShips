// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerControllerImpl.h"

#include "ActionPlayerController.h"
#include "NausTFGMultiPlayer/Client/Controllers/ActionGameController.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
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
		
		presentationController = NewObject<UActionGameController>(GetOwner());

		presentationController->Init(Cast<AActionPlayerController>(GetOwner()));
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

	DOREPLIFETIME(AActionPlayerControllerImpl, teamMate);
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
		//tiene que ser true
		teamMate->SetActorHiddenInGame(true);
		
	}
}


void AActionPlayerControllerImpl::PlayDeath()
{

}

void AActionPlayerControllerImpl::LoadGameStateHUD()
{

	if(!HasAuthority() && presentationController)
	{

		Cast<UActionGameController>(presentationController)->LoadGameStateHUD();
	}

}

void AActionPlayerControllerImpl::BeginPlay()
{
	Super::BeginPlay();

	//InitializePresentationController();


}

void AActionPlayerControllerImpl::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AActionPlayerControllerImpl::CreaMenus()
{

	bool bIsLocalPlayerContropller = Cast<AActionPlayerController>(GetOwner())->IsLocalPlayerController();

	if (bIsLocalPlayerContropller && presentationController)
	{
		presentationController->CreaMenus();

	}

}

void AActionPlayerControllerImpl::LoadHUD()
{

}


