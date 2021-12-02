// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "PilotActionPawn.generated.h"

class URotationComponent;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API APilotActionPawn : public AActionPawn
{
	GENERATED_BODY()


public:

	APilotActionPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;


protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	URotationComponent* rotationComponent;

};
