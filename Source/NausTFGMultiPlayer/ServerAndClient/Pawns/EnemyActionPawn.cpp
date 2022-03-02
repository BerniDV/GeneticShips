// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActionPawn.h"

#include "Components/BoxComponent.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Controllers/AIBaseController.h"
#include "Net/UnrealNetwork.h"

AEnemyActionPawn::AEnemyActionPawn()
{
	
	bReplicates = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComponent"));
	RootComponent = boxComponent;

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("staticMesh"));
	meshComponent->SetupAttachment(RootComponent);

	enemyChromosome = nullptr;

	id = -1;
}

void AEnemyActionPawn::SetID(int32 newEnemyID)
{

	id = newEnemyID;
}

int32 AEnemyActionPawn::GetID()
{

	return id;
}


void AEnemyActionPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnemyActionPawn, enemyChromosome);
	DOREPLIFETIME(AEnemyActionPawn, id);
}

void AEnemyActionPawn::SetRandomGenes()
{

	enemyChromosome->SetRandomGenes();
}

void AEnemyActionPawn::ApplyFenotipe()
{

	enemyChromosome->ApplyFenotipe();
}

void AEnemyActionPawn::SetChromosome(AChromosome* newChromosome)
{

	enemyChromosome = newChromosome;

	ApplyFenotipe();
}

AChromosome* AEnemyActionPawn::GetChromosome()
{

	return enemyChromosome;
}

float AEnemyActionPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float currentHealth = 100.f;

	if (AAIBaseController* IAC = Cast<AAIBaseController>(GetOwner()))
	{

		currentHealth = IAC->ApplyDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);


	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Current Health: %f"), currentHealth));

	return currentHealth;
}

void AEnemyActionPawn::PlayDeath()
{

	Destroy();
}

void AEnemyActionPawn::BeginPlay()
{
	Super::BeginPlay();
		

}

void AEnemyActionPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

		
}

void AEnemyActionPawn::Destroyed()
{

	Super::Destroyed();

}
