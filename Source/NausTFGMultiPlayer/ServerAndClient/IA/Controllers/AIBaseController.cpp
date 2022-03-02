// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBaseController.h"

#include "EnemyManager.h"
#include "ParameterCollection.h"
#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/Server/GameModes/ActionGameMode.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"

AAIBaseController::AAIBaseController()
{

	PrimaryActorTick.bCanEverTick = true;
	health = 100.f;
}

void AAIBaseController::BeginPlay()
{
	Super::BeginPlay();

	
	//target = UGameplayStatics::GetActorOfClass(GetWorld(), APilotActionPawn::StaticClass());
	TArray<AActor*> targetArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APilotActionPawn::StaticClass(), targetArray);

	for (auto x : targetArray)
	{
		APilotActionPawn* targetOption = Cast<APilotActionPawn>(x);
		if(x && targetOption->GetPawnTeamId().IsSet() && targetOption->GetPawnTeamId().GetValue() >= 0)
		{

			target = Cast<APilotActionPawn>(x);
			break;
		}
	}
}

void AAIBaseController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AActor* myPawn = GetPawn();

	

	if(myPawn && target)
	{

		FVector myLocation = myPawn->GetActorLocation();
		
		FVector targetLocation = target->GetPredictedPosition();
		FVector nextLocation = FMath::VInterpConstantTo(myLocation, targetLocation, DeltaSeconds, 500.f);
	
		myPawn->SetActorLocation(nextLocation);
		
	}
	
}

void AAIBaseController::Destroyed()
{

	Super::Destroyed();
}

float AAIBaseController::ApplyDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	float newHealth = health - DamageAmount;

	if (newHealth <= 0)
	{
		newHealth = 0.f;
		AEnemyActionPawn* myPawn = Cast<AEnemyActionPawn>(GetPawn());

		myPawn->PlayDeath();

		//Buscar otra manera que respete la cadena de mando y no necesite guardar una rteferencia al enemy manager
		enemyManager->DeleteEnemy(myPawn->GetID());
	}

	health = newHealth;
	return newHealth;
}

void AAIBaseController::SetEnemyManager(AEnemyManager* enemyController)
{

	enemyManager = enemyController;
}
