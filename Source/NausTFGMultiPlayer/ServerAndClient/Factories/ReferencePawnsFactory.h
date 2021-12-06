// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ReferencePawnsFactory.generated.h"

enum class NausTFGRolTypes : uint8;
class UPilotReferenceFactory;
enum class NausTFGPawnReferencesFactories_Enum : uint8;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UReferencePawnsFactory : public UObject
{
	GENERATED_BODY()

public:

	static UReferencePawnsFactory* GetInstance();

	virtual UClass* CreateReference();

	UReferencePawnsFactory* GetFactory(NausTFGRolTypes factory);

protected:

	UReferencePawnsFactory();

private:

	static UReferencePawnsFactory* referenceFactory;

	UReferencePawnsFactory* pilotReferenceFactory;
	UReferencePawnsFactory* artilleryReferenceFactory;

};


