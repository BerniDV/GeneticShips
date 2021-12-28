// Fill out your copyright notice in the Description page of Project Settings.


#include "RotationComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/ActionPawn.h"
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
	yawRotation = 0.f;
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


	
}

void URotationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(URotationComponent, rotation);
}

FRotator URotationComponent::GetRotation()
{

	return rotation;
}

void URotationComponent::ExecuteRotation(float value)
{

	yawRotation += value;

	rotation = FRotator(0.f, yawRotation, 0.f);

	//if(!GetOwner()->HasAuthority())
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%f"), value));

	ApplyRotation();

}


void URotationComponent::ApplyRotation()
{

	AActionPlayerControllerImpl* playerControllerImpl = Cast<AActionPlayerControllerImpl>(GetOwner());

	AActionPlayerController* playerController = Cast<AActionPlayerController>(playerControllerImpl->GetOwner());

	Cast<AActionPawn>(playerController->GetPawn())->Server_SetRotation(rotation);
}

