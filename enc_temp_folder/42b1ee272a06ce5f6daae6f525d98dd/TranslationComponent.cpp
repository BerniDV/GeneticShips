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

	movementSpeedInCm = 300.f;

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
	timeSinceLastInput = 0;
	updateTimeStamp = 0;
	lastUpdateTimeStamp = 0;
	lastInterpolationSpeed = 0.f;
	interpolationSpeed = movementSpeedInCm;

}


// Called every frame

void UTranslationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//interpolation with the predicted position

	currentTime += DeltaTime;

	if(GetOwner()->GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{

		direction = (forwardDirection + rightDirection);
		direction.Normalize();
		position += direction * DeltaTime * movementSpeedInCm;
		predictedPosition = position;
		interpolatedPosition = position;
		Move_Server(position, direction, currentTime);
		Cast<AActionPawn>(GetOwner())->SetActorLocation(position);

	}
	/*
	if(DistinctEnough(interpolatedPosition, predictedPosition))
	{

		Cast<AActionPawn>(GetOwner())->SetActorLocation(position);
		lastInterpolationSpeed = movementSpeedInCm;
		interpolationSpeed = lastInterpolationSpeed;
	}
	*/
	
	if (!SimilarEnough(interpolatedPosition, predictedPosition) && bisMoving) {

		//poner lastpredicted y no position??
		//lastInterpolationSpeed = interpolationSpeed;
		//interpolationSpeed = ((predictedPosition - interpolatedPosition).Size()) / delay;

		//No se para que, no me acuerdo 
		//interpolationSpeed = (interpolationSpeed + lastInterpolationSpeed) / 2;

		//Barrera de seguridad para controlar correcciones muy graves que puedan desestabilizar la sincronia de velocidades y provocar un movimiento de lag
		//interpolationSpeed = FMath::Clamp(interpolationSpeed, interpolationSpeed, movementSpeedInCm + 200.f);
		
		//comprovar que si es menor que la velocidad minima sea igual a la velocidad minima, en caso contrario puede ser el resultado
		interpolatedPosition = FMath::VInterpConstantTo(interpolatedPosition, predictedPosition, DeltaTime, interpolationSpeed); 

	}
	else
	{	//En caso de llegar a una interpolacion completa significa que el jugador ya no se mueve, y por lo tanto rectificamos el ultimo movimiento predicho y lo ponemos en la posición final
		//No obstante creo que es mas facil comprovar que se ha terminado de mover replicando la direccion y cuando sea 0 poner a falso el movimiento
		//bisMoving = false;
		predictedPosition = position;
		Cast<AActionPawn>(GetOwner())->SetActorLocation(position);
	}

	Cast<AActionPawn>(GetOwner())->SetActorLocation(interpolatedPosition);

	
	if (!GetOwner()->HasAuthority())
	{

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, position.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, predictedPosition.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, interpolatedPosition.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("%f"), interpolationSpeed));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("%d"), bisMoving));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("%f"), delay));

	}
		
}

void UTranslationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTranslationComponent, position, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UTranslationComponent, updateTimeStamp, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UTranslationComponent, direction, COND_SkipOwner);
	 
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


void UTranslationComponent::Move_Server_Implementation(FVector movement, FVector _direction, float _currentTime)
{

	direction = _direction;
	position = movement;
	updateTimeStamp = _currentTime;

	Cast<AActionPawn>(GetOwner())->SetActorLocation(position);

	if(GetOwner()->HasAuthority())
	{

		ApplyMovementWithInterpolation();

	}
}

bool UTranslationComponent::Move_Server_Validate(FVector movement, FVector _direction, float _currentTime)
{

	return true;
}


bool UTranslationComponent::SimilarEnough(FVector FPosition, FVector SPosition)
{

	return UKismetMathLibrary::Abs(FPosition.X - SPosition.X) < 0.1f && UKismetMathLibrary::Abs(FPosition.Y - SPosition.Y) < 0.1f && UKismetMathLibrary::Abs(FPosition.Z - SPosition.Z) < 0.1f;
}

bool UTranslationComponent::DistinctEnough(FVector FPosition, FVector SPosition)
{

	return UKismetMathLibrary::Abs(FPosition.X - SPosition.X) > 3.f || UKismetMathLibrary::Abs(FPosition.Y - SPosition.Y) > 3.f || UKismetMathLibrary::Abs(FPosition.Z - SPosition.Z) > 3.f;

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
		lastDirection = FVector::ZeroVector;

	}else
	{
		if(direction == FVector::ZeroVector)
		{

			bisMoving = false;

		}else
		{

			bisMoving = true;
		}

		lastDirection = direction;

		if(!bisMoving)
		{

			interpolatedPosition = position;
		}

		lastPosition = currentPosition;
		currentPosition = position;

		delay = updateTimeStamp - lastUpdateTimeStamp;

		lastUpdateTimeStamp = updateTimeStamp;

		if (delay > startPredictionInMs) {

			if (delay > 0.5f)
				delay = 0.21f;

			lastPredictedPosition = predictedPosition;
			predictedPosition = position + (movementSpeedInCm * direction * delay);
			interpolationSpeed = ((predictedPosition - interpolatedPosition).Size()) / delay;

		}else
		{

			predictedPosition = position;
			interpolationSpeed = movementSpeedInCm;
		}

		

	}

}


