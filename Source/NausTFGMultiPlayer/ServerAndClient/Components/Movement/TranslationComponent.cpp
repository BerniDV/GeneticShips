// Fill out your copyright notice in the Description page of Project Settings.


#include "TranslationComponent.h"

#include "ParameterCollection.h"
#include "Kismet/KismetMathLibrary.h"
#include "NausTFGMultiPlayer/ServerAndClient/GameStates/ActionGameState.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UTranslationComponent::UTranslationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTranslationComponent::BeginPlay()
{
	Super::BeginPlay();

	position = GetOwner()->GetActorLocation();
	lastPosition = position;
	movementReplicatedPack.position = position;
	predictedPosition = position;
	interpolatedPosition = position;
	direction = FVector::ZeroVector;
	bfirstUpdate = true;
	delay = 1;
	currentTime = 0;
	accelerationInMS = 0;
	currentspeed = FVector::ZeroVector;
	defaultMaxAcceleration = 0.f;
	maxAcceleration = 0.f;
	defaultMaxSpeed = 0.f;
	maxSpeed = 0.f;
	accelerationSpeed = 0.f;
	decelerationSpeed = 0.f;
	speedDropRate = 0.f;
	maneuverabilityInPercent = 0.f;

}

void UTranslationComponent::Inicialite(float _speedDropRate, float _defaultMaxAcceleration, float _defaultMaxSpeed, float _maxAcceleration, float _maxSpeed, float _accelerationSpeed, float _decelerationSpeed, float _meneuverabilityInPercent)
{

	defaultMaxAcceleration = _defaultMaxAcceleration;
	maxAcceleration = _maxAcceleration;
	defaultMaxSpeed = _defaultMaxSpeed;
	maxSpeed = _maxSpeed;
	accelerationSpeed = _accelerationSpeed;
	decelerationSpeed = _decelerationSpeed;
	speedDropRate = _speedDropRate;
	maneuverabilityInPercent = _meneuverabilityInPercent;
	movementReplicatedPack.maneuverabilityInPercent = maneuverabilityInPercent;

}

bool UTranslationComponent::SimilarEnough(FVector v1, FVector v2)
{
	FVector diff = v2 - v1;
	return diff.Size() < 50.f;
}

float UTranslationComponent::GetCurrenntSpeed()
{
	return currentspeed.Size();
}

FVector UTranslationComponent::GetReplicatedPosition()
{

	return position;
}

FVector UTranslationComponent::GetPredictedPosition()
{

	return predictedPosition;
}

float UTranslationComponent::GetInterpolationSpeed()
{

	return interpolationSpeed;
}

FVector UTranslationComponent::GetLastPosition()
{

	return lastPosition;
}




// Called every frame

void UTranslationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GetOwner()->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{

		if (accelerationInMS > maxAcceleration)
			accelerationInMS = maxAcceleration;

		if(currentspeed.Size() > maxSpeed - 50.f)
		{
			currentspeed = FMath::VInterpConstantTo(currentspeed, FVector::ZeroVector, DeltaTime, currentspeed.Size() / 1.5f);

		}


		if(AActionGameState* GS = Cast<AActionGameState>(GetWorld()->GetGameState()))
		{

			currentTime = GS->GetServerWorldTimeSeconds();
		}
		

		direction = (forwardDirection + rightDirection);
		direction.Normalize();

		if(direction == FVector::ZeroVector && currentspeed.Size() > 0.f)
		{

			accelerationInMS = FMath::FInterpConstantTo(accelerationInMS, 0.f, DeltaTime, decelerationSpeed);

		}else
		{

			accelerationInMS = FMath::FInterpConstantTo(accelerationInMS, maxAcceleration, DeltaTime, accelerationSpeed);

		}

		if(accelerationInMS == 0.0f)
		{

			currentspeed = FMath::VInterpConstantTo(currentspeed, FVector::ZeroVector, DeltaTime, speedDropRate);

		}else
		{

			currentspeed = CalculateSpeedNextIteration(currentspeed, maneuverabilityInPercent, direction, accelerationInMS, DeltaTime);
		}

		lastPosition = position;

		position = CalculatePositionNextIteration(position, currentspeed, DeltaTime);
		predictedPosition = position;
		interpolatedPosition = position;



		if (currentspeed.Size() != 0)
			Move_Server(position, direction, currentspeed, currentTime, accelerationInMS, maneuverabilityInPercent);

		Cast<AActionPawn>(GetOwner())->SetActorLocation(position, true);
		
	}
	
	//Si nos hemos parado corregimos a la ultima posiciopn confirmada conocida, en caso contrario seguimos interpolando entre la actual y la que hemos predecido
	//Como siempre predecimos segun la ultima confirmada las pequeñas correciones se hacen implicitamente
	if (GetOwner()->GetLocalRole() != ENetRole::ROLE_AutonomousProxy && !SimilarEnough(position, lastPosition)) {

		interpolatedPosition = FMath::VInterpConstantTo(interpolatedPosition, predictedPosition, DeltaTime, interpolationSpeed); 
		Cast<AActionPawn>(GetOwner())->SetActorLocation(interpolatedPosition, true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Prediction");
	}
	else
	{	//En caso de llegar a una interpolacion casi completa significa que el jugador ya no se mueve, y por lo tanto rectificamos el ultimo movimiento predicho y lo ponemos en la posición final
		predictedPosition = position;
		//interpolationSpeed = (GetOwner()->GetActorLocation() - position).Size() / delay;
		
		//interpolatedPosition = FMath::VInterpConstantTo(GetOwner()->GetActorLocation(), position, DeltaTime, interpolationSpeed);
		interpolatedPosition = FMath::Lerp(GetOwner()->GetActorLocation(), position, 0.3);
		Cast<AActionPawn>(GetOwner())->SetActorLocation(interpolatedPosition, true);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Correction");
	}

	lastPosition = position;
		
}

void UTranslationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTranslationComponent, movementReplicatedPack, COND_SkipOwner);
	 
}

void UTranslationComponent::MoveRight(float movement)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());	   

	//rightDirection = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::Y) * movement;
	rightDirection = GetOwner()->GetActorRightVector() * movement;

}


void UTranslationComponent::MoveForward(float movement)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());

	//forwardDirection = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::X) * movement;
	forwardDirection = GetOwner()->GetActorForwardVector() * movement;

}


void UTranslationComponent::Move_Server_Implementation(FVector movement, FVector _direction, FVector _currentSpeed, float _currentTime, float _accelerationInMs, float _maneuverabilityInPercent)
{

	
	movementReplicatedPack.Update(movement, _direction, _currentSpeed, _accelerationInMs, _currentTime, _maneuverabilityInPercent);


	if(GetOwner()->HasAuthority())
	{

		ApplyMovementWithInterpolation();

	}
}

bool UTranslationComponent::Move_Server_Validate(FVector movement, FVector _direction, FVector _currentSpeed, float _currentTime, float accelerationInMs, float _maneuverabilityInPercent)
{

	return true;
}



void UTranslationComponent::SetMaxAcceleration(float _maxAcceleration)
{

	maxAcceleration = _maxAcceleration;
}

void UTranslationComponent::SetCurrentAcceleration(float _currentAcceleration)
{

	accelerationInMS = _currentAcceleration;
}

void UTranslationComponent::SetMaxSpeed(float _maxSpeed)
{

	maxSpeed = _maxSpeed;
}

void UTranslationComponent::SetCurrentSpeed(float _currentSpeed)
{

	FVector currentDirection = currentspeed;
	currentDirection.Normalize();
	currentspeed = _currentSpeed * currentDirection;
}

float UTranslationComponent::GetMaxAcceleration()
{

	return maxAcceleration;
}

float UTranslationComponent::GetMaxSpeed()
{

	return maxSpeed;
}

void UTranslationComponent::ResetSpeedAndAcceleration()
{

	maxAcceleration = defaultMaxAcceleration;
	maxSpeed = defaultMaxSpeed;



}

void UTranslationComponent::BoostSpeed(float Value)
{

	FVector pilotBoost = Value * direction * 4.f;

	currentspeed += pilotBoost;

}

FVector UTranslationComponent::CalculateSpeedNextIteration(FVector _currentSpeed, float _maneuverabilityInPercent, FVector _direction, float _acelerationInMS, float time)
{

	FVector speedUp = FVector::ZeroVector;

	if (_currentSpeed.Size() < maxSpeed)
	{

		float maneuverabilityInValue = (((_maneuverabilityInPercent * 7.f) / 100.f) * maxSpeed / 1000.f);

		speedUp = (_acelerationInMS * _direction * maneuverabilityInValue * time);

	}

	return speedUp + _currentSpeed;

}

FVector UTranslationComponent::CalculatePositionNextIteration(FVector _position, FVector _currentSpeed, float time)
{

	FVector nextPosition = FVector::ZeroVector;

	nextPosition = _position + (_currentSpeed * time);

	return nextPosition;

}


void UTranslationComponent::ApplyMovementWithInterpolation()
{
	//Multiplicar velocidad por vector de direccion por tiempo que hemos estado sin updatear
	
	if(bfirstUpdate)
	{

		bfirstUpdate = false;
		predictedPosition = movementReplicatedPack.position;

		lastPosition = movementReplicatedPack.position;
		currentPosition = movementReplicatedPack.position;	
		interpolatedPosition = movementReplicatedPack.position;

	}else
	{

		position = movementReplicatedPack.position;
		direction = movementReplicatedPack.direction;
		currentspeed = movementReplicatedPack.currentspeed;
		accelerationInMS = movementReplicatedPack.accelerationInMS;
		maneuverabilityInPercent = movementReplicatedPack.maneuverabilityInPercent;
		float updateTimeStamp = movementReplicatedPack.updateTimeStamp;

		lastPosition = currentPosition;
		currentPosition = position;

		if (AActionGameState* GS = Cast<AActionGameState>(GetWorld()->GetGameState()))
		{

			currentTime = GS->GetServerWorldTimeSeconds();
		}

		delay = currentTime - updateTimeStamp;

		delay = FMath::Abs(delay);

		predictedPosition = CalculatePositionNextIteration(position, currentspeed, delay);

		currentspeed = CalculateSpeedNextIteration(currentspeed, maneuverabilityInPercent, direction, accelerationInMS, delay);

		predictedPosition = CalculatePositionNextIteration(predictedPosition, currentspeed, delay);

		interpolationSpeed = currentspeed.Size();

	}

}


