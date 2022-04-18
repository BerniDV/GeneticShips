// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBaseController.h"

#include "EnemyManager.h"
#include "ParameterCollection.h"
#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/Server/GameModes/ActionGameMode.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/EnemyActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"
#include "NausTFGMultiPlayer/ServerAndClient/IA/Chromosome.h"


AAIBaseController::AAIBaseController()
{

	PrimaryActorTick.bCanEverTick = true;
	health = 100.f;
	fireTimeTest = 0.f;
	cadencyFire = 10.f;
	bCanShoot = true;

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


	if (myPawn && target) {

		//Si esta muy lejos no puede disparar
		if ((myPawn->GetActorLocation() - target->GetActorLocation()).Size() < 50000 && HasAuthority())
		{


			bCanShoot = true;

		}
		else
		{

			bCanShoot = false;
		}


		if(HasAuthority())
		{

			FVector myLocation = myPawn->GetActorLocation();

			FVector targetLocation = target->GetPredictedPosition();
			FVector targetEnemyVector = targetLocation - myLocation;

			targetEnemyVector.Normalize();

			FRotator newRotation = FMath::RInterpConstantTo(myPawn->GetActorRotation(), targetEnemyVector.Rotation(), DeltaSeconds, 100.f);

			myPawn->ExecuteRotation(newRotation);

			myPawn->MoverForward(1);

			fireTimeTest += DeltaSeconds;

		}

		

		if (fireTimeTest > cadencyFire && enemyState != EnemyState::Dead && bCanShoot && HasAuthority())
		{
			//Si el enemigo esta muerto no deberia poder disparar
			fireTimeTest = 0.f;
			myPawn->Server_Fire(myPawn->GetActorLocation(), target->GetActorLocation());


		}
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

void AAIBaseController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//Coger valor genetico de disparo
	AEnemyActionPawn* myPawn = Cast<AEnemyActionPawn>(InPawn);

	cadencyFire = myPawn->GetChromosome()->GetGene(Gene::fireCadancy);
	health = myPawn->GetChromosome()->GetGene(Gene::health);

}

void AAIBaseController::SetEnemyCanShoot(bool canShoot)
{

	bCanShoot = canShoot;
}

void AAIBaseController::SetHealth(float _health)
{

	health = _health;
}
