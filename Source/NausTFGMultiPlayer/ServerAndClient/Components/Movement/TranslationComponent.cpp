// Fill out your copyright notice in the Description page of Project Settings.


#include "TranslationComponent.h"

#include "Kismet/KismetMathLibrary.h"
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
	predictedPosition = position;
	interpolatedPosition = position;
	direction = FVector::ZeroVector;
	bfirstUpdate = true;
	bisMoving = false;
	delay = 1;
	currentTime = 0;
	updateTimeStamp = 0;
	lastUpdateTimeStamp = 0;
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

}


// Called every frame

void UTranslationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//interpolation with the predicted position

	if(GetOwner()->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{

		if (accelerationInMS > maxAcceleration)
			accelerationInMS = maxAcceleration;

		if(currentspeed.Size() > maxSpeed - 50.f)
		{
			currentspeed = FMath::VInterpConstantTo(currentspeed, FVector::ZeroVector, DeltaTime, currentspeed.Size() / 1.5f);

		}
			

		currentTime += DeltaTime;

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

			currentspeed += CalculateSpeedNextIteration(DeltaTime);
		}

		

		position = CalculatePositionNextIteration(DeltaTime);
		predictedPosition = position;
		interpolatedPosition = position;
		Move_Server(position, direction, currentspeed, currentTime, accelerationInMS, maneuverabilityInPercent);
		Cast<AActionPawn>(GetOwner())->SetActorLocation(position);

	}

	bisMoving = currentspeed != FVector::ZeroVector;

	//mientras la interpolacion no llegue al destino seguimos interpolando
	if (bisMoving && GetOwner()->GetLocalRole() != ENetRole::ROLE_AutonomousProxy) {


		interpolatedPosition = FMath::VInterpConstantTo(interpolatedPosition, predictedPosition, DeltaTime, interpolationSpeed); 
		Cast<AActionPawn>(GetOwner())->SetActorLocation(interpolatedPosition);
	}
	else
	{	//En caso de llegar a una interpolacion completa significa que el jugador ya no se mueve, y por lo tanto rectificamos el ultimo movimiento predicho y lo ponemos en la posición final
		predictedPosition = position;
		interpolatedPosition = position;
		Cast<AActionPawn>(GetOwner())->SetActorLocation(position);
	}

	

	
	if (!GetOwner()->HasAuthority())
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("interpolation speed: %f"), interpolationSpeed));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "current speed: " + currentspeed.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "direction " + direction.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("acceleration: %f"), accelerationInMS));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("delay: %f"), delay));

	}
		
}

void UTranslationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTranslationComponent, position, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UTranslationComponent, accelerationInMS, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UTranslationComponent, maneuverabilityInPercent, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UTranslationComponent, updateTimeStamp, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UTranslationComponent, direction, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UTranslationComponent, currentspeed, COND_SkipOwner);
	 
}

void UTranslationComponent::MoveRight(float movement)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());	   

	rightDirection = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::Y) * movement;

	if (direction != FVector::ZeroVector)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, direction.ToString());

}


void UTranslationComponent::MoveForward(float movement)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());

	forwardDirection = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::X) * movement;

	if (direction != FVector::ZeroVector)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, direction.ToString());

}


void UTranslationComponent::Move_Server_Implementation(FVector movement, FVector _direction, FVector _currentSpeed, float _currentTime, float _accelerationInMs, float _maneuverabilityInPercent)
{

	direction = _direction;
	position = movement;
	updateTimeStamp = _currentTime;
	currentspeed = _currentSpeed;
	accelerationInMS = _accelerationInMs;
	maneuverabilityInPercent = _maneuverabilityInPercent;


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

	currentspeed = _currentSpeed * direction;
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

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Silver, "boost speed: " + pilotBoost.ToString());
}

FVector UTranslationComponent::CalculateSpeedNextIteration(float time)
{

	FVector speedUp = FVector::ZeroVector;

	if (currentspeed.Size() < maxSpeed)
	{

		float maneuverabilityInValue = (((maneuverabilityInPercent * 7.f) / 100.f) * maxSpeed / 1000.f);

		speedUp = (accelerationInMS * direction * maneuverabilityInValue * time);

	}

	return speedUp;

}

FVector UTranslationComponent::CalculatePositionNextIteration(float time)
{

	FVector nextPosition = FVector::ZeroVector;

	nextPosition = position + (currentspeed * time);

	return nextPosition;

}


void UTranslationComponent::ApplyMovementWithInterpolation()
{
	//Multiplicar velocidad por vector de direccion por tiempo que hemos estado sin updatear
	
	if(bfirstUpdate)
	{

		bfirstUpdate = false;
		bisMoving = false;
		predictedPosition = position;
		lastPredictedPosition = position;

		lastPosition = position;
		currentPosition = position;
		interpolatedPosition = position;

	}else
	{

		lastPosition = currentPosition;
		currentPosition = position;

		delay = updateTimeStamp - lastUpdateTimeStamp;

		lastUpdateTimeStamp = updateTimeStamp;

		//mientras no tenga un reloj sincronizado necesito crear una frontera de delay màximo (en el caso que el jugador no se mueva no quiero delay infinito)
		if (delay > 0.5f)
			//delay = 0.31f;
			delay = 0.01f;
		
		if (delay > startPredictionInMs) {

			lastPredictedPosition = predictedPosition;

			currentspeed += CalculateSpeedNextIteration(delay);

			predictedPosition = CalculatePositionNextIteration(delay);

			interpolationSpeed = ((predictedPosition - interpolatedPosition).Size()) / delay;

		}else
		{

			predictedPosition = position;
			interpolationSpeed = (lastPosition - currentPosition).Size() / delay;
		}

	}

}


