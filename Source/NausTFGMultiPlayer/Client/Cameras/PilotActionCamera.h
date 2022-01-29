// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionCamera.h"
#include "PilotActionCamera.generated.h"

/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API APilotActionCamera : public AActionCamera
{
	GENERATED_BODY()

public:

	APilotActionCamera();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	
};
