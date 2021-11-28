// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReferencePawnsFactory.h"
#include "PilotReferenceFactory.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UPilotReferenceFactory : public UReferencePawnsFactory
{
	GENERATED_BODY()


public:

	

	static UReferencePawnsFactory* GetInstance();

	virtual UClass* CreateReference() override;

private:

	UPilotReferenceFactory();

	UClass* reference;

	static UReferencePawnsFactory* referenceFactory;
};
