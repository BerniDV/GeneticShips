// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReferencePawnsFactory.h"
#include "ArtilleryReferenceFactory.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API UArtilleryReferenceFactory : public UReferencePawnsFactory
{
	GENERATED_BODY()

public:



	static UReferencePawnsFactory* GetInstance();

	virtual UClass* CreateReference() override;

private:

	UArtilleryReferenceFactory();

	UClass* reference;

	static UReferencePawnsFactory* referenceFactory;
};
