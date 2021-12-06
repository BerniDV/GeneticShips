// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerControllerImpl.h"
#include "NausTFGMultiPlayer/Client/Controllers/InitMenuController.h"

#include "Net/UnrealNetwork.h"


AActionPlayerControllerImpl::AActionPlayerControllerImpl()
{

	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	//Normas de replicacion, hacer networkmanager para replicar segun proximidad (replicar solo pawns?)
	//bAlwaysRelevant = true;
	pruebaReplicate = 0;
	
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

	DOREPLIFETIME(AActionPlayerControllerImpl, pruebaReplicate);
}

UPresentationController* AActionPlayerControllerImpl::GetPresentationController()
{

	return presentationController;
}

void AActionPlayerControllerImpl::Rotate(float turnValue)
{

}


void AActionPlayerControllerImpl::BeginPlay()
{
	Super::BeginPlay();

	InitializePresentationController();
	
}

void AActionPlayerControllerImpl::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//Nom�s prova de replica, en un futur s'ha deliminar
	if(HasAuthority())
		pruebaReplicate += 1;
}


