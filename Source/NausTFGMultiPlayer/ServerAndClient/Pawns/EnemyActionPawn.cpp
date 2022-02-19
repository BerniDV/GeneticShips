// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActionPawn.h"

#include "Components/BoxComponent.h"

AEnemyActionPawn::AEnemyActionPawn()
{

	bReplicates = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	RootComponent = boxComponent;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

	id = -1;
}

void AEnemyActionPawn::SetID(int32 newEnemyID)
{

	id = newEnemyID;
}
