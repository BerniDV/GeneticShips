// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionPawn.h"

// Sets default values
AActionPawn::AActionPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if(GEngine)
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Pawn Prepared"));
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

