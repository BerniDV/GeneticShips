// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/NoExportTypes.h"
#include "NausTFGEnums.generated.h"

/**
 * 
 */

enum class NausTFGRolTypes : uint8;

struct MatchOptions
{

	MatchOptions(const FString& i_options, int team)
	{

		roleSelected = (NausTFGRolTypes)FCString::Atoi(*UGameplayStatics::ParseOption(i_options, TEXT("Role")));
		teamID = team;
	}

	NausTFGRolTypes roleSelected;
	int teamID;
};

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