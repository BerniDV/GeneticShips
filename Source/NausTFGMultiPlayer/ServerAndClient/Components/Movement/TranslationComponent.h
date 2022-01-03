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
	void Move_Server(FVector movement, FVector _direction, float _currentTime);

	bool SimilarEnough(FVector FPosition, FVector SPosition);

	bool DistinctEnough(FVector FPosition, FVector SPosition);


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

	float delay;
	float currentTime;
	float timeSinceLastInput;

	UPROPERTY(Replicated)
	float updateTimeStamp;
	float lastUpdateTimeStamp;

	float interpolationSpeed;
	float lastInterpolationSpeed;

	bool bfirstUpdate;

	bool bisMoving;
		
};


