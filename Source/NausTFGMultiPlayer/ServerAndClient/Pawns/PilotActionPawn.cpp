// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPawn.h"

#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/RotationComponent.h"
#include "Net/UnrealNetwork.h"

APilotActionPawn::APilotActionPawn()
{

	bReplicates = true;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Pawn Prepared"));

	rotationComponent = CreateDefaultSubobject<URotationComponent>(TEXT("rotationComponent"));
	
}

void APilotActionPawn::BeginPlay()
{
	Super::BeginPlay();
}

void APilotActionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void APilotActionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", rotationComponent, &URotationComponent::CalculateRotation);
}

void APilotActionPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(AMainMenuPlayerState, rolSelected);
}
