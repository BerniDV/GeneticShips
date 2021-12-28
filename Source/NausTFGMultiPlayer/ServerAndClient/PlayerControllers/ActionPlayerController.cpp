// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"

#include "ArtilleryActionPlayerController.h"
#include "PilotActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "Net/UnrealNetwork.h"



AActionPlayerController::AActionPlayerController()
{
	
	bReplicates = true;
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
		
		InputComponent->BindAxis("Turn", playerControllerImpl, &AActionPlayerControllerImpl::Rotate);
		InputComponent->BindAxis("MoveForward", playerControllerImpl, &AActionPlayerControllerImpl::MoveForward);
		InputComponent->BindAxis("MoveRight", playerControllerImpl, &AActionPlayerControllerImpl::MoveRight);
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

}


void AActionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//A tots o només client owner?
	DOREPLIFETIME_CONDITION(AActionPlayerController, playerControllerImpl, COND_OwnerOnly);
}


void AActionPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void AActionPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsLocalPlayerController() && playerControllerImpl)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), playerControllerImpl->pruebaReplicate));
}
