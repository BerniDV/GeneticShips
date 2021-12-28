// Fill out your copyright notice in the Description page of Project Settings.


#include "TranslationComponent.h"

#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerControllerImpl.h"
#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UTranslationComponent::UTranslationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	position = FVector::ZeroVector;

	movementSpeedInCm = 140.f;
}


// Called when the game starts
void UTranslationComponent::BeginPlay()
{
	Super::BeginPlay();

	position = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UTranslationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!GetOwner()->HasAuthority())
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), position.X));
}

void UTranslationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UTranslationComponent, position, COND_SkipOwner);
}

void UTranslationComponent::MoveRight(float movement)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());

	FVector rightVector = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::Y);


	position += movement * rightVector * GetWorld()->DeltaTimeSeconds * movementSpeedInCm;

	ApplyMovement();

	MoveRight_Server(position);
}

void UTranslationComponent::MoveForward(float movement)
{

	APilotActionPawn* myPawn = Cast<APilotActionPawn>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(myPawn->GetController());

	FVector forwardVector = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::X);

	position += movement * forwardVector * GetWorld()->DeltaTimeSeconds * movementSpeedInCm;

	ApplyMovement();

	MoveForward_Server(position);
}

void UTranslationComponent::MoveForward_Server_Implementation(FVector movement)
{

	position = movement;

}

bool UTranslationComponent::MoveForward_Server_Validate(FVector movement)
{

	return true;
}


void UTranslationComponent::MoveRight_Server_Implementation(FVector movement)
{

	position = movement;

}

bool UTranslationComponent::MoveRight_Server_Validate(FVector movement)
{

	return true;
}


void UTranslationComponent::ApplyMovement()
{


	Cast<AActionPawn>(GetOwner())->SetActorLocation(position);
	
}


