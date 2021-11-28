// Fill out your copyright notice in the Description page of Project Settings.


#include "ArtilleryReferenceFactory.h"

#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ArtilleryActionPawn.h"


UReferencePawnsFactory* UArtilleryReferenceFactory::referenceFactory = nullptr;

UArtilleryReferenceFactory::UArtilleryReferenceFactory()
{

	ConstructorHelpers::FClassFinder <AArtilleryActionPawn> refArtilleryActionPawnBP(TEXT("/Game/ServerAndClient/Pawns/ArtilleryActionPawn_BP"));
	reference = refArtilleryActionPawnBP.Class;
}


UReferencePawnsFactory* UArtilleryReferenceFactory::GetInstance()
{

	if (referenceFactory != nullptr)
	{

		return referenceFactory;
	}

	referenceFactory = NewObject<UArtilleryReferenceFactory>();
	return referenceFactory;
}

UClass* UArtilleryReferenceFactory::CreateReference()
{

	return reference;
}


