// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPlayerController.h"
#include <optional>
#include "NausTFGMultiPlayer/Client/Controllers/MainMenuController.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Factories/ReferencePawnsFactory.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ArtilleryActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"
#include "Net/UnrealNetwork.h"

class AActionPlayerController::ActionPlayerControllerImpl
{
public:
	virtual UClass* GetDefaultPawn() = 0;
protected:
	UClass* m_reference;
};

class PilotActionPlayerControllerImpl : public AActionPlayerController::ActionPlayerControllerImpl
{
public:
	PilotActionPlayerControllerImpl();
	UClass* GetDefaultPawn() override;
};

class ArtilleryActionPlayerControllerImpl : public AActionPlayerController::ActionPlayerControllerImpl
{
public:
	ArtilleryActionPlayerControllerImpl();
	UClass* GetDefaultPawn() override;
};

AActionPlayerController::AActionPlayerController()
{

	bReplicates = true;
	defaultPawn = nullptr;

	
}

void AActionPlayerController::InitializePresentationController()
{

	if (IsLocalPlayerController())
	{
		//Placeholder para no crash, se sustituye por inGameMenu
		presentationController = NewObject<UMainMenuController>();

		presentationController->Init(this);
	}
}

void AActionPlayerController::BindSignals()
{
	

}

UClass* AActionPlayerController::GetDefaultPawn()
{

	return m_impl->GetDefailtPwan();
}

void AActionPlayerController::InitializeDefaultPawn(UReferencePawnsFactory* factoryType)
{

	/*
	if (type == NausTFGRolTypes_Enum::PilotActionRolType)
	{

		defaultPawn = pilotClass;

	}else if (type == NausTFGRolTypes_Enum::ArtilleryActionRolType)
	{
		defaultPawn = artilleryClass;
	}*/

	defaultPawn = factoryType->CreateReference();

}

void AActionPlayerController::Initialize(NausTFGRolTypes_Enum i_type)
{
	switch (i_type)
	{
	case NausTFGRolTypes_Enum::ArtilleryActionRolType:
		m_impl = new ArtilleryActionPlayerControllerImpl();
		break;
	case NausTFGRolTypes_Enum::PilotActionRolType:
		m_impl = new PilotActionPlayerControllerImpl();
		break;
	default:
		break;
	}
}

void AActionPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionPlayerController, defaultPawn);
}

AActionPlayerController::PilotActionPlayerControllerImpl::PilotActionPlayerControllerImpl()
{
	ConstructorHelpers::FClassFinder <APilotActionPawn> refPilotActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/PilotActionPawn_BP"));
	m_reference = refPilotActionPawnBP.Class;
}

UClass* AActionPlayerController::PilotActionPlayerControllerImpl::GetDefaultPawn()
{
	return m_reference;
}

AActionPlayerController::ArtilleryActionPlayerControllerImpl::ArtilleryActionPlayerControllerImpl()
{
	ConstructorHelpers::FClassFinder <AArtilleryActionPawn> refArtilleryActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/ArtilleryActionPawn_BP"));
	m_reference = refArtilleryActionPawnBP.Class;
}

UClass* AActionPlayerController::ArtilleryActionPlayerControllerImpl::GetDefaultPawn()
{
	return m_reference;
}
