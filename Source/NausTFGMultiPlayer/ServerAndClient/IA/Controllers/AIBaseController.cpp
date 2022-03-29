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
	fireTimeTest = 0.f;
}

void AAIBaseController::BindSignals()
{

	AEnemyActionPawn* myPawn = Cast<AEnemyActionPawn>(GetPawn());

	myPawn->signalOnEnemyDead.AddDynamic(this, &AAIBaseController::OnEnemyDead);
}

void AAIBaseController::BeginPlay()
{
	Super::BeginPlay();

	enemyState = EnemyState::Alive;
	
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

	AEnemyActionPawn* myPawn = Cast<AEnemyActionPawn>(GetPawn());

	

	if(myPawn && target && HasAuthority())
	{
		
		FVector myLocation = myPawn->GetActorLocation();
		
		FVector targetLocation = target->GetPredictedPosition();
		FVector targetEnemyVector = targetLocation - myLocation;

		//FVector nextLocation = FMath::VInterpConstantTo(myLocation, targetLocation, DeltaSeconds, 500.f);
	
		//myPawn->SetPosition(nextLocation);

		targetEnemyVector.Normalize();

		myPawn->ExecuteRotation(targetEnemyVector.Rotation());

		myPawn->MoverForward(1);
		//myPawn->MoverRight(targetEnemyVector.Y);
		
	}

	fireTimeTest += DeltaSeconds;

	if(fireTimeTest > 5.f && HasAuthority() && enemyState != EnemyState::Dead)
	{
		//Si el enemigo esta muerto no deberia poder disparar
		fireTimeTest = 0.f;
		myPawn->Server_Fire(myPawn->GetActorLocation(), target->GetActorLocation());

		
	}
	
}

void AAIBaseController::Destroyed()
{
	//EL pawn esta muerto antes de llamar esto y se jode, hcer qyue no mueran, solo invisibles
	//Buscar otra manera que respete la cadena de mando y no necesite guardar una rteferencia al enemy manager
	//UE_LOG(LogTemp, Warning, TEXT("Enemy Controller Destroyed"));
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
	}

	

	health = newHealth;
	return newHealth;
}

void AAIBaseController::MoveForward(float movement)
{

	AEnemyActionPawn* myPawn = Cast<AEnemyActionPawn>(GetPawn());

	myPawn->MoverForward(movement);
}

void AAIBaseController::MoveRight(float movement)
{
	AEnemyActionPawn* myPawn = Cast<AEnemyActionPawn>(GetPawn());

	myPawn->MoverRight(movement);
}

void AAIBaseController::OnEnemyDead()
{

	enemyState = EnemyState::Dead;
}
