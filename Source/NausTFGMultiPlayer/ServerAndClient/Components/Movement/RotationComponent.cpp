// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerController.h"
#include "NausTFGMultiPlayer/ServerAndClient/PlayerControllers/ActionPlayerControllerImpl.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
URotationComponent::URotationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	rotation = FRotator::ZeroRotator;

}


// Called when the game starts
void URotationComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void URotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(GetOwnerRole() == ROLE_SimulatedProxy)
	{

		FRotator currentRotation = GetOwner()->GetActorRotation();

		currentRotation = FMath::RInterpConstantTo(currentRotation, rotation, DeltaTime, 0.01);

		GetOwner()->SetActorRotation(currentRotation);

	}
	
}

void URotationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(URotationComponent, rotation, COND_SkipOwner);
}

FRotator URotationComponent::GetRotation()
{

	return rotation;
}

void URotationComponent::ExecuteRotation(FRotator rotator)
{

	AActionPawn* myPawn = Cast<AActionPawn>(GetOwner());

	rotation = rotator;
	myPawn->SetActorRotation(rotator);

	Server_ExecuteRotation(rotator);

}


void URotationComponent::Server_ExecuteRotation_Implementation(FRotator rotator)
{

	rotation = rotator;

	GetOwner()->SetActorRotation(rotator);
}

bool URotationComponent::Server_ExecuteRotation_Validate(FRotator rotator)
{

	return true;
}



