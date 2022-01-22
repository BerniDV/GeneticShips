// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TranslationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAUSTFGMULTIPLAYER_API UTranslationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTranslationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	void MoveForward(float movement);

	void MoveRight(float movement);

	UFUNCTION(Server, Unreliable, WithValidation)
	void Move_Server(FVector movement, FVector _direction, FVector _currentSpeed, float _currentTime, float _accelerationInMs, float _maneuverabilityInPercent);

	void SetMaxAcceleration(float _maxAcceleration);
	void SetCurrentAcceleration(float _currentAcceleration);

	void SetMaxSpeed(float _maxSpeed);
	void SetCurrentSpeed(float _currentSpeed);

	float GetMaxAcceleration();

	float GetMaxSpeed();

	void ResetSpeedAndAcceleration();

	void BoostSpeed(float Value);

	FVector CalculateSpeedNextIteration(float time);

	FVector CalculatePositionNextIteration(float time);

	void Inicialite(float _speedDropRate, float _defaultMaxAcceleration, float _defaultMaxSpeed, float _maxAcceleration, float _maxSpeed, float _accelerationSpeed, float _decelerationSpeed, float _meneuverabilityInPercent);

private:

	UFUNCTION()
	void ApplyMovementWithInterpolation();

	void ApplyMovement();

	UPROPERTY(ReplicatedUsing = ApplyMovementWithInterpolation)
	FVector position;

	FVector lastPosition;
	FVector currentPosition;

	FVector predictedPosition;
	FVector lastPredictedPosition;

	FVector interpolatedPosition;

	UPROPERTY(Replicated)
	FVector direction;
	FVector lastDirection;

	FVector forwardDirection;
	FVector rightDirection;

	float movementSpeedInCm;

	UPROPERTY(Replicated)
	FVector currentspeed;

	UPROPERTY(Replicated)
	float accelerationInMS;

	float delay;
	float currentTime;

	UPROPERTY(Replicated)
	float updateTimeStamp;
	float lastUpdateTimeStamp;

	float interpolationSpeed;

	bool bfirstUpdate;

	bool bisMoving;

	const float startPredictionInMs = 0.15f;

	float defaultMaxAcceleration;

	float defaultMaxSpeed;

	float maxAcceleration;

	float maxSpeed;

	float accelerationSpeed;

	float decelerationSpeed;

	UPROPERTY(Replicated)
	float maneuverabilityInPercent;

	float speedDropRate;
		
};


