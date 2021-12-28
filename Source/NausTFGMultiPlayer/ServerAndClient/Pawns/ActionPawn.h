// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ActionPawn.generated.h"

class UTranslationComponent;
UCLASS()
class NAUSTFGMULTIPLAYER_API AActionPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AActionPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	UFUNCTION(Server, Reliable, WithValidation)
	virtual void Server_SetRotation(FRotator rotator);

	UFUNCTION(NetMulticast, Reliable)
	virtual void Client_SetRotation(FRotator rotator);

	virtual void MoveForward(float movement);

	virtual void MoveRight(float movement);

	virtual void ExecuteRotation(float turnValue);



};
