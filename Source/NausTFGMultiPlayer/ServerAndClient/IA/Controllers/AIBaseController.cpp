// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBaseController.h"

#include "ParameterCollection.h"
#include "Kismet/GameplayStatics.h"
#include "NausTFGMultiPlayer/ServerAndClient/Pawns/PilotActionPawn.h"

AAIBaseController::AAIBaseController()
{

	PrimaryActorTick.bCanEverTick = true;
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
