// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "enemyMovementComponent.generated.h"

USTRUCT(BlueprintType)
struct FMovementReplicatedPack
{
	
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector position;

	UPROPERTY()
	FVector direction;

	UPROPERTY()
	FVector currentspeed;

	UPROPERTY()
	float accelerationInMS;

	UPROPERTY()
	float updateTimeStamp;

	UPROPERTY()
	float maneuverabilityInPercent;


	FMovementReplicatedPack()
	{

		position = FVector::ZeroVector;
		direction = FVector::ZeroVector;
		currentspeed = FVector::ZeroVector;
		accelerationInMS = 0.f;
		updateTimeStamp = 0.f;
		maneuverabilityInPercent = 0.f;
	}

	void Update(FVector _position, FVector _direction, FVector _currentspeed, float _accelerationInMS, float _updateTimeStamp, float _maneuverabilityInPercent)
	{

		position = _position;
		direction = _direction;
		currentspeed = _currentspeed;
		accelerationInMS = _accelerationInMS;
		updateTimeStamp = _updateTimeStamp;
		maneuverabilityInPercent = _maneuverabilityInPercent;
	}

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAUSTFGMULTIPLAYER_API UenemyMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UenemyMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps)const override;

	void MoveForward(float movement);

	void MoveRight(float movement);

	void SetMaxAcceleration(float _maxAcceleration);
	void SetCurrentAcceleration(float _currentAcceleration);

	void SetMaxSpeed(float _maxSpeed);
	void SetCurrentSpeed(float _currentSpeed);

	float GetMaxAcceleration();

	float GetMaxSpeed();

	void ResetSpeedAndAcceleration();

	void BoostSpeed(float Value);

	FVector CalculateSpeedNextIteration(FVector _currentSpeed, float _maneuverabilityInPercent, FVector _direction, float _acelerationInMS, float time);

	FVector CalculatePositionNextIteration(FVector _position, FVector _currentSpeed, float time);

	void Inicialite(float _speedDropRate, float _defaultMaxAcceleration, float _defaultMaxSpeed, float _maxAcceleration, float _maxSpeed, float _accelerationSpeed, float _decelerationSpeed, float _meneuverabilityInPercent);

	bool SimilarEnough(FVector v1, FVector v2);

	float GetCurrenntSpeed();

	FVector GetReplicatedPosition();

	FVector GetPredictedPosition();

	float GetInterpolationSpeed();

	FVector GetLastPosition();

private:

	UFUNCTION()
	void ApplyMovementWithInterpolation();

	FVector position;

	FVector lastPosition;
	FVector currentPosition;

	FVector predictedPosition;

	FVector interpolatedPosition;

	FVector direction;

	FVector forwardDirection;
	FVector rightDirection;

	FVector currentspeed;

	float accelerationInMS;

	float delay;
	float currentTime;

	float interpolationSpeed;

	bool bfirstUpdate;

	float defaultMaxAcceleration;

	float defaultMaxSpeed;

	float maxAcceleration;

	float maxSpeed;

	float accelerationSpeed;

	float decelerationSpeed;

	float maneuverabilityInPercent;

	float speedDropRate;


	UPROPERTY(ReplicatedUsing = ApplyMovementWithInterpolation)
	FMovementReplicatedPack movementReplicatedPack;
};
