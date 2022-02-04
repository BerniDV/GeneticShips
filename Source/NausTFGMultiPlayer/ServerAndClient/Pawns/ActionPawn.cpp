// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPawn.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AActionPawn::AActionPawn()
{

	bReplicates = true;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if(GEngine)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pawn Prepared"));

	maxHealth = 100.f;
	health = maxHealth;
}

// Called when the game starts or when spawned
void AActionPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActionPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AActionPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AActionPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AActionPawn, health);
	
}

void AActionPawn::MoveForward(float movement)
{
}

void AActionPawn::MoveRight(float movement)
{
}

void AActionPawn::ExecuteRotation(FRotator rotator)
{
}

void AActionPawn::ImpulseON()
{

}

void AActionPawn::ImpulseOff()
{

}

void AActionPawn::DecelerationON()
{

}

void AActionPawn::DecelerationOff()
{

}

void AActionPawn::BoostSpeed(float Value)
{

}

void AActionPawn::Fire()
{

}

float AActionPawn::GetHealth()
{

	return health;
}

void AActionPawn::SetHealth(float value)
{

	if(value <= maxHealth)
		health = value;
}

void AActionPawn::AddHealth(float value)
{
	if(health + value <= maxHealth)
		health += value;
}

void AActionPawn::OnHealthUpdate()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Tu vida es: %f"), health));
}

void AActionPawn::Client_SetRotation_Implementation(FRotator rotator)
{

	SetActorRotation(rotator);
}

void AActionPawn::Server_SetRotation_Implementation(FRotator rotator)
{

	Client_SetRotation(rotator);
}

bool AActionPawn::Server_SetRotation_Validate(FRotator rotator)
{

	return true;
}


