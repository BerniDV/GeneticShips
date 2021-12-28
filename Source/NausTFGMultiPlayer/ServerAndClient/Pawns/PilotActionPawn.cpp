// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Components/Movement/TranslationComponent.h"
#include "Net/UnrealNetwork.h"

APilotActionPawn::APilotActionPawn()
{

	bReplicates = true;
	
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pilot Pawn Prepared"));

	translationComponent = CreateDefaultSubobject<UTranslationComponent>(TEXT("translationComponent"));
	translationComponent->SetIsReplicated(true);

	NetUpdateFrequency = 2.5f;
	
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


	
}

void APilotActionPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APilotActionPawn, translationComponent);
	
}

void APilotActionPawn::MoveForward(float movement)
{

	translationComponent->MoveForward(movement);
}

void APilotActionPawn::MoveRight(float movement)
{

	translationComponent->MoveRight(movement);
}