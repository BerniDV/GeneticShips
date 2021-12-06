// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NausTFGEnums.generated.h"

/**
 * 
 */


UENUM()
enum class NausTFGRolTypes : uint8
{
	PilotActionRolType,

	ArtilleryActionRolType,

	NoneType
};

UENUM()
enum class NausTFGPawnReferencesFactories_Enum : uint8
{
	PilotActionPawnReferenceFactory,

	ArtilleryActionPawnReferenceFactory,

};

/*
UCLASS()
class NAUSTFGMULTIPLAYER_API UNausTFGEnums : public UObject
{
	GENERATED_BODY()
	
};
*/