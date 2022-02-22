// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBaseController.generated.h"

class APilotActionPawn;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AAIBaseController : public AAIController
{
	GENERATED_BODY()

public:

	AAIBaseController();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:

	APilotActionPawn* target;
	
};
