// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActionPawn.h"
#include "PilotActionPawn.generated.h"

class UBoxComponent;
class USpringArmComponent;
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


	virtual void MoveForward(float movement) override;

	virtual void MoveRight(float movement) override;

	virtual void ExecuteRotation(float turnValue) override;

	virtual void ImpulseON() override;

	virtual void ImpulseOff() override;

	virtual void DecelerationON() override;

	virtual void DecelerationOff() override;

	virtual void BoostSpeed(float Value) override;

	USpringArmComponent* GetSpringArmComponent();

protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Replicated)
		UTranslationComponent* translationComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Replicated)
		URotationComponent* rotationComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USpringArmComponent* springArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* collisionBox;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* meshComponent;

private:

	float movementSpeedInCm;
	float defaultMaxAcceleration;
	float defaultMaxSpeed;
	float maxAcceleration;
	float maxSpeed;
	float accelerationSpeed;
	float decelerationSpeed;
	float speedDropRate;
	float maneuverabilityInPercent;

	


};
