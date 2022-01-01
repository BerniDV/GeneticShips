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

	movementSpeedInCm = 140.f;

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
	current = 0;

}


// Called every frame
void UTranslationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//interpolation with the predicted position

	current += DeltaTime;

	if (!SimilarEnough(interpolatedPosition, predictedPosition) && bisMoving) {
		
		interpolatedPosition = FMath::Lerp(interpolatedPosition, predictedPosition, DeltaTime/(float)delay);

		//interpolatedPosition = position + movementSpeedInCm * direction * current;

	}
	else if(!SimilarEnough(interpolatedPosition, position))
	{	//En caso de llegar a una interpolacion completa significa que el jugador ya no se mueve, y por lo tanto rectificamos el ultimo movimiento predicho y lo ponemos en la posición final
		bisMoving = false;
		predictedPosition = position;
		interpolatedPosition = FMath::Lerp(interpolatedPosition, position, DeltaTime/(delay));
	}

	Cast<AActionPawn>(GetOwner())->SetActorLocation(interpolatedPosition);


	//if (!GetOwner()->HasAuthority())
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, position.ToString() + "  " + predictedPosition.ToString() + "  " + interpolatedPosition.ToString() + "  " + direction.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), (float)((float)current / (float)delay)));
}

void UTranslationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTranslationComponent, position, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(UTranslationComponent, direction, COND_SkipOwner);

}

void UTranslationComponent::MoveRight(float movement)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());

	direction = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::Y);


	position += movement * direction * GetWorld()->DeltaTimeSeconds * movementSpeedInCm;

	ApplyMovement();

	Move_Server(position, direction);
}

void UTranslationComponent::Move_Server_Implementation(FVector movement, FVector _direction)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());
	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());
	direction = _direction;
	position = movement;
	
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, direction.ToString());

	ApplyMovement();
}

bool UTranslationComponent::Move_Server_Validate(FVector movement, FVector _direction)
{

	return true;
}


void UTranslationComponent::MoveForward(float movement)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());

	direction = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::X);

	position += movement * direction * GetWorld()->DeltaTimeSeconds * movementSpeedInCm;

	ApplyMovement();

	Move_Server(position, direction);
}


bool UTranslationComponent::SimilarEnough(FVector FPosition, FVector SPosition)
{

	return UKismetMathLibrary::Abs(FPosition.X - SPosition.X) < 0.1f && UKismetMathLibrary::Abs(FPosition.Y - SPosition.Y) < 0.1f && UKismetMathLibrary::Abs(FPosition.Z - SPosition.Z) < 0.1f;
}

void UTranslationComponent::ApplyMovementWithInterpolation()
{
	//Multiplicar velocidad por vector de direccion por tiempo que hemos estado sin updatear
	
	if(bfirstUpdate)
	{

		bfirstUpdate = false;
		predictedPosition = position;

	}else
	{
		//interpolatedPosition = position;

		delay = 0.2f;
		current = 0;
		predictedPosition = position + movementSpeedInCm * direction * GetWorld()->DeltaTimeSeconds * delay;

	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Update");

	bisMoving = true;
}

void UTranslationComponent::ApplyMovement()
{

	predictedPosition = position;
	interpolatedPosition = position;
	Cast<AActionPawn>(GetOwner())->SetActorLocation(position);

}


