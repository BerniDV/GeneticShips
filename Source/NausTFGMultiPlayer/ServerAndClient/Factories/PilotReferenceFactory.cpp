// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotReferenceFactory.h"

#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"


UReferencePawnsFactory* UPilotReferenceFactory::referenceFactory = nullptr;

UPilotReferenceFactory::UPilotReferenceFactory()
{

	ConstructorHelpers::FClassFinder <APilotActionPawn> refPilotActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/PilotActionPawn_BP"));
	reference = refPilotActionPawnBP.Class;
	
}

UReferencePawnsFactory* UPilotReferenceFactory::GetInstance()
{

	if (referenceFactory != nullptr)
	{

		return referenceFactory;
	}

	referenceFactory = NewObject<UPilotReferenceFactory>();
	return referenceFactory;
}

UClass* UPilotReferenceFactory::CreateReference()
{

	return reference;
}
