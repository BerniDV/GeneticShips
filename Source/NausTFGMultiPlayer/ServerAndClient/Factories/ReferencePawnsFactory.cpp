// Fill out your copyright notice in the Description page of Project Settings.


#include "ReferencePawnsFactory.h"

#include "ArtilleryReferenceFactory.h"
#include "NausTFGMultiPlayer/ServerAndClient/DataObjects/NausTFGEnums.h"
#include "NausTFGMultiPlayer/ServerAndClient/Factories/PilotReferenceFactory.h"

UReferencePawnsFactory* UReferencePawnsFactory::referenceFactory = nullptr;

UReferencePawnsFactory::UReferencePawnsFactory()
{
	
}


UReferencePawnsFactory* UReferencePawnsFactory::GetInstance()
{

	if (referenceFactory != nullptr)
	{

		return referenceFactory;
	}

	referenceFactory = NewObject<UReferencePawnsFactory>();
	return referenceFactory;
}

UClass* UReferencePawnsFactory::CreateReference()
{

	return nullptr;
}

UReferencePawnsFactory* UReferencePawnsFactory::GetFactory(NausTFGRolTypes factory)
{

	UReferencePawnsFactory* resultFactory = nullptr;

	if(factory == NausTFGRolTypes::PilotActionRolType)
	{

		resultFactory = pilotReferenceFactory = UPilotReferenceFactory::GetInstance();

	}else if(factory == NausTFGRolTypes::ArtilleryActionRolType)
	{

		resultFactory = artilleryReferenceFactory = UArtilleryReferenceFactory::GetInstance();
	}

	return resultFactory;
}
