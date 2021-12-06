// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerControllerDefaultBehaviour.h"
#include "ActionPlayerControllerImpl.generated.h"

class UPresentationController;
/**
 * 
 */
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionPlayerControllerImpl : public AActor
{
	GENERATED_BODY()


public:

	AActionPlayerControllerImpl();

	 virtual void InitializePresentationController();

	 virtual void BindSignals();

	virtual UClass* GetDefaultPawn();

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	UPresentationController* GetPresentationController();

	virtual void Rotate(float turnValue);

	UPROPERTY(Replicated)
	int pruebaReplicate;

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:

	UPresentationController* presentationController;

	

};
